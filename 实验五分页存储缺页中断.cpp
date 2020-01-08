#include<iostream>
#include<cmath>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<queue>
#include<stack>
#include<time.h>
#define Max 1024
using namespace std;
int len;//页面号序列长度 
int str[Max];///页面号序列
int block;///系统为进程分配的物理块
int que[Max];///模拟队列
struct Page
{
    int sta;///内存位当前状态
    int A;///访问位
    int M;///修改位
    int tim;///距离上一次访问时长
    int dis;///距离上一次访问距离
} Q[Max];
void init()
{
    printf("请输入页面号序列长度：");
    cin>>len;
    printf("请输入页面号序列：");
    for(int i=1; i<=len; i++) cin>>str[i];
    printf("请输入系统为进程分配的物理块：");
    cin>>block;
    for(int i=0; i<=block; i++)
        que[i]=-1;///初始值置为-1代表当前物理块为空
}
void print(int x)
{
 
    printf("当前需访问第 %d 页   ",str[x]);
    for(int i=1; i<=block; i++)
    {
        printf("[%3d] ",que[i]);
    }
    puts("");
}
void FIFO()
{
    printf("选择使用FIFO算法进行页面置换\n");
    init();
    int flag=1;///记录要进行页面置换的位置
    int num=0;//记录缺页 
    for(int i=1; i<=len; i++)
    {
        int j;
        int ok=0;
        for(j=1; j<=block; j++)
        {
            if(str[i]==que[j])
                ok=1;
        }
        if(que[block]==-1&&!ok)//内存中没有，并且内存未满
        {
            for(j=1; j<=block; j++)
            {
                if(que[j]==-1)
                {
                    que[j]=str[i];
                    break;
                }
            }
        }
        else if(que[block]!=-1&&!ok)//内存中没有，但是内存已满需要置换
        {
            printf("产生缺页中断\n");
            num++;
            que[flag]=str[i];
            flag++;
            if(flag>block)
                flag=1;
        }
        print(i);
    }
    puts("");
    printf("共缺页%d次，FIFO算法执行结束\n\n",num);
}
void LRU() 
{
    printf("选择使用LRU算法进行页面置换\n");
    init();
    int num=0;
    for(int i=1; i<=len; i++)
    {
        int ok=0,j;
        for(j=1; j<=block; j++)
        {
            if(str[i]==que[j])
                ok=1;
        }
        if(que[block]==-1&&!ok)//内存中没有，并且内存未满
        {
            for(j=1; j<=block; j++)
            {
                if(que[j]==-1)
                {
                    que[j]=str[i];
                    break;
                }
            }
        }
        else if(que[block]!=-1&&!ok)//内存中没有，但是内存已满需要置换
        {
            printf("产生缺页中断\n");
            num++;
            for(j=2; j<=block; j++) que[j-1]=que[j];
            que[block]=str[i];
        }
        else if(que[block]==-1&&ok)//内存中有，但是内存未满，只需要调换位置类型1
        {
            int k;//记录与当前页面好匹配的页面号位置
            for(j=1; j<=block; j++)
            {
                if(que[j]==str[i])
                {
                    k=j;
                }
            }
            for(j=k+1; j<=block; j++)
            {
                if(que[j]==-1)
                    break;
                else
                    que[j-1]=que[j];
            }
            que[j-1]=str[i];
        }
        else if(que[block]!=-1&&ok)//内存中有，但是内存已满，只需要调换位置类型2
        {
            int k;//记录与当前页面好匹配的页面号位置
            for(j=1; j<=block; j++)
            {
                if(que[j]==str[i])
                {
                    k=j;
                }
            }
            for(j=k+1; j<=block; j++)
                que[j-1]=que[j];
            que[block]=str[i];
        }
        print(i);
    }
    puts("");
    printf("共缺页%d次，LRU算法执行结束\n\n",num);
}
//判断页面是否已经被修改
bool change()
{
    if((rand()%4+1) == 1 )
    {
        printf("该页面被修改!\n");
        return true;
    }
    else
        return false;
}
//检测页号是否在内存中并把访问位和修改位置1
bool inblock(int num)
{
    for(int i=1; i<=block; i++)
    {
        if(Q[i].sta == str[num])
        {
            if(change())
            {
                Q[i].A=1;
                Q[i].M=1;
            }
            else
            {
                Q[i].A=1;
                Q[i].M=0;
            }
            return true;
        }
    }
    return false;
}
int Search()
{
    int j;
    for(j=1;j<=block;j++)
    {
        if(Q[j].A==0&&Q[j].M==0)
            return j;
    }
    for(j=1;j<=block;j++ )
    {
        if(Q[j].A==0&&Q[j].M==1)
            return j;
        Q[j].A=0;
    }
    for(j=1;j<=block;j++ )
    {
        Q[j].A=0;
    }
    return Search();
}
int snum=0;
void SNRU()//使用情况与置换代价 
{
    printf("选择使用改进型Clock算法进行页面置换\n");
    init();
    int j;
    for(int i=1; i<=block; i++)
    {
        Q[i].sta=-1;
        Q[i].A=0;
        Q[i].M=0;
    }
    for(int i=1; i<=len; i++)
    {
        printf("当前需访问的页面为 %d !\n",str[i]);
        int judge=inblock(i);
        if(judge==0&&Q[block].sta!=-1)//页面未存在于内存中并且内存已满
        {
            j=Search();
            Q[j].sta=str[i];
            snum++;
            printf("产生缺页中断\n");
        }
        else if(judge==0&&Q[block].sta==-1)//内存未满，并且页面未存在于内存中
        {
            for(int k=1;k<=block;k++)
            {
                if(Q[k].sta==-1){
                    Q[k].sta=str[i];
                    snum++;
                	printf("产生缺页中断\n");
                    break;
                }
            }
        }
        for(int k=1;k<=block;k++)
        {
            printf("[ %3d ] ",Q[k].sta);
        }
        puts("");
    }
    puts("");
    printf("共缺页%d次，改进的CLOCK算法执行结束\n\n",snum);
    snum=0;
}
int main()
{
    while(1)
    {
        printf("请选择要使用的页面置换算法或选择退出:\n");
        printf("***************************************************************\n");
        printf("1.FIFO置换算法   2.LRU置换算法   3.改进型CLOCK算法    4.退出\n");
        printf("***************************************************************\n");
        int choice;
        cin>>choice;
        if(choice==1) 
			FIFO();
        else if(choice==2) 
			LRU();
        else if(choice==3) 
			SNRU();
        else if(choice==4) 
			break;
        else
        {
            printf("输入有错误，请重新选择！\n");
        }
    }
    return 0;
}
//测试数据：
// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 
