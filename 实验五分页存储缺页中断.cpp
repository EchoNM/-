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
int len;//ҳ������г��� 
int str[Max];///ҳ�������
int block;///ϵͳΪ���̷���������
int que[Max];///ģ�����
struct Page
{
    int sta;///�ڴ�λ��ǰ״̬
    int A;///����λ
    int M;///�޸�λ
    int tim;///������һ�η���ʱ��
    int dis;///������һ�η��ʾ���
} Q[Max];
void init()
{
    printf("������ҳ������г��ȣ�");
    cin>>len;
    printf("������ҳ������У�");
    for(int i=1; i<=len; i++) cin>>str[i];
    printf("������ϵͳΪ���̷��������飺");
    cin>>block;
    for(int i=0; i<=block; i++)
        que[i]=-1;///��ʼֵ��Ϊ-1����ǰ�����Ϊ��
}
void print(int x)
{
 
    printf("��ǰ����ʵ� %d ҳ   ",str[x]);
    for(int i=1; i<=block; i++)
    {
        printf("[%3d] ",que[i]);
    }
    puts("");
}
void FIFO()
{
    printf("ѡ��ʹ��FIFO�㷨����ҳ���û�\n");
    init();
    int flag=1;///��¼Ҫ����ҳ���û���λ��
    int num=0;//��¼ȱҳ 
    for(int i=1; i<=len; i++)
    {
        int j;
        int ok=0;
        for(j=1; j<=block; j++)
        {
            if(str[i]==que[j])
                ok=1;
        }
        if(que[block]==-1&&!ok)//�ڴ���û�У������ڴ�δ��
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
        else if(que[block]!=-1&&!ok)//�ڴ���û�У������ڴ�������Ҫ�û�
        {
            printf("����ȱҳ�ж�\n");
            num++;
            que[flag]=str[i];
            flag++;
            if(flag>block)
                flag=1;
        }
        print(i);
    }
    puts("");
    printf("��ȱҳ%d�Σ�FIFO�㷨ִ�н���\n\n",num);
}
void LRU() 
{
    printf("ѡ��ʹ��LRU�㷨����ҳ���û�\n");
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
        if(que[block]==-1&&!ok)//�ڴ���û�У������ڴ�δ��
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
        else if(que[block]!=-1&&!ok)//�ڴ���û�У������ڴ�������Ҫ�û�
        {
            printf("����ȱҳ�ж�\n");
            num++;
            for(j=2; j<=block; j++) que[j-1]=que[j];
            que[block]=str[i];
        }
        else if(que[block]==-1&&ok)//�ڴ����У������ڴ�δ����ֻ��Ҫ����λ������1
        {
            int k;//��¼�뵱ǰҳ���ƥ���ҳ���λ��
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
        else if(que[block]!=-1&&ok)//�ڴ����У������ڴ�������ֻ��Ҫ����λ������2
        {
            int k;//��¼�뵱ǰҳ���ƥ���ҳ���λ��
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
    printf("��ȱҳ%d�Σ�LRU�㷨ִ�н���\n\n",num);
}
//�ж�ҳ���Ƿ��Ѿ����޸�
bool change()
{
    if((rand()%4+1) == 1 )
    {
        printf("��ҳ�汻�޸�!\n");
        return true;
    }
    else
        return false;
}
//���ҳ���Ƿ����ڴ��в��ѷ���λ���޸�λ��1
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
void SNRU()//ʹ��������û����� 
{
    printf("ѡ��ʹ�øĽ���Clock�㷨����ҳ���û�\n");
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
        printf("��ǰ����ʵ�ҳ��Ϊ %d !\n",str[i]);
        int judge=inblock(i);
        if(judge==0&&Q[block].sta!=-1)//ҳ��δ�������ڴ��в����ڴ�����
        {
            j=Search();
            Q[j].sta=str[i];
            snum++;
            printf("����ȱҳ�ж�\n");
        }
        else if(judge==0&&Q[block].sta==-1)//�ڴ�δ��������ҳ��δ�������ڴ���
        {
            for(int k=1;k<=block;k++)
            {
                if(Q[k].sta==-1){
                    Q[k].sta=str[i];
                    snum++;
                	printf("����ȱҳ�ж�\n");
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
    printf("��ȱҳ%d�Σ��Ľ���CLOCK�㷨ִ�н���\n\n",snum);
    snum=0;
}
int main()
{
    while(1)
    {
        printf("��ѡ��Ҫʹ�õ�ҳ���û��㷨��ѡ���˳�:\n");
        printf("***************************************************************\n");
        printf("1.FIFO�û��㷨   2.LRU�û��㷨   3.�Ľ���CLOCK�㷨    4.�˳�\n");
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
            printf("�����д���������ѡ��\n");
        }
    }
    return 0;
}
//�������ݣ�
// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 
