#include <stdio.h>
#include <algorithm>
#include <string>
#define maxsize 1000 //定义最大数组域
using namespace std;
//先进先出调度算法
void FCFS(int array[],int m)
{
    int sum=0,j,i,now;
    float average;
    printf("\n 请输入当前的磁道号：");
    scanf("%d",&now);
    printf("\n 调度结果:  ");
    printf("%d ",now);
    for(i=0; i<m; i++) 
		printf("%d ",array[i]);
    sum=abs(now-array[0]);
    for(j=1; j<m; j++) sum+=abs(array[j]-array[j-1]); //累计总的移动距离
    average=(float)sum/m;//计算平均寻道长度
    printf("\n 移动的总道数： %d \n",sum);
    printf(" 平均寻道长度： %f \n",average);
}
 
//最短时间优先调度算法
void SSTF(int array[],int m)
{
    int temp;
    int k=1;
    int now,l,r;
    int i,j,sum=0;
    float avg;
    for(i=0; i<m; i++)
    {
        for(j=i+1; j<m; j++) //对磁道号进行从小到大排列
        {
            if(array[i]>array[j])//两磁道号之间比较
            {
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }
    }
    for( i=0; i<m; i++) //输出排序后的磁道号数组
        printf("%d  ",array[i]);
    printf("\n 请输入当前的磁道号：");
    scanf("%d",&now);
    printf("\n SSTF调度结果:  ");
    if(array[m-1]<=now)//判断整个数组里的数是否都小于当前磁道号
    {
        for(i=m-1; i>=0; i--) //将数组磁道号从大到小输出
            printf("%d  ",array[i]);
        sum=now-array[0];//计算移动距离
    }
    else if(array[0]>=now)//判断整个数组里的数是否都大于当前磁道号
    {
        for(i=0; i<m; i++) //将磁道号从小到大输出
            printf("%d  ",array[i]);
        sum=array[m-1]-now;//计算移动距离
    }
    else
    {
        while(array[k]<now)//逐一比较以确定K值
        {
            k++;
        }
        l=k-1;
        r=k;
        //确定当前磁道在已排的序列中的位置
        while((l>=0)&&(r<m))
        {
            if((now-array[l])<=(array[r]-now))//判断最短距离
            {
                printf("%d  ",array[l]);
                sum+=now-array[l];//计算移动距离
                now=array[l];
                l=l-1;
            }
            else
            {
                printf("%d  ",array[r]);
                sum+=array[r]-now;//计算移动距离
                now=array[r];
                r=r+1;
            }
        }
        if(l==-1)
        {
            for(j=r; j<m; j++)
            {
                printf("%d  ",array[j]);
            }
            sum+=array[m-1]-array[0];//计算移动距离
        }
        else
        {
            for(j=l; j>=0; j--)
            {
                printf("%d  ",array[j]);
            }
            sum+=array[m-1]-array[0];//计算移动距离
        }
    }
    avg=(float)sum/m;
    printf("\n 移动的总道数： %d \n",sum);
    printf(" 平均寻道长度： %f \n",avg);
}
// SCAN
void SCAN(int array[], int m)
{	int now, direction;
    printf("\n 请输入当前的磁道号： ");
    scanf("%d",&now);
    printf("\n 请选择磁头移动方向：1向外，2向里\n");
    scanf("%d", &direction);
    std::sort(array, array + m);
    int sum = 0;
    float avg;
    printf("\n 调度结果: ");
    if(direction == 1)
    {
        int index = std::lower_bound(array, array + m, now) - array;
        for(int i = index; i < m; i++)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        for(int i = index - 1; i >= 0; i--)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        avg=(float)sum/m;//计算平均寻道长度
        printf("\n 移动的总道数： %d \n",sum);
        printf(" 平均寻道长度： %f \n",avg);
    }
    else
    {
        int index = std::lower_bound(array, array + m, now) - array;
        for(int i = index - 1; i >= 0; i--)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        for(int i = index; i < m; i++)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        avg=(float)sum/m;//计算平均寻道长度
        printf("\n 移动的总道数： %d \n",sum);
        printf(" 平均寻道长度： %f \n",avg);
    }
}

void CSCAN(int array[], int m)
{
    int now,direction;
    printf("\n 请输入当前的磁道号： ");
    scanf("%d",&now);
    printf("\n 请选择磁头移动方向：1向外，2向里\n");
    scanf("%d", &direction);
    sort(array, array + m);
    int sum = 0;
    float avg;
    printf("\n 调度结果: ");
    if(direction == 1)
    {
        int index = std::lower_bound(array, array + m, now) - array;
        for(int i = index; i < m; i++)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        for(int i = 0; i < index; i++)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        avg=(float)sum/m;//计算平均寻道长度
        printf("\n 移动的总道数： %d \n",sum);
        printf(" 平均寻道长度： %f \n",avg);
    }
    else
    {
        int index = std::lower_bound(array, array + m, now) - array;
        for(int i = index - 1; i >= 0; i--)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        for(int i = m - 1; i >= index; i--)
        {
            sum += abs(now - array[i]);
            now = array[i];
            printf("%d ", array[i]);
        }
        avg=(float)sum/m;//计算平均寻道长度
        printf("\n 移动的总道数： %d \n",sum);
        printf(" 平均寻道长度： %f \n",avg);
    }
}
 
// 操作界面
int main()
{	int count;
    int cidao[maxsize];//定义磁道号数组
    int i=0;
    int n;
    printf("磁盘调度算法模拟\n");
    printf("输入磁道数量：\n");
    scanf("%d",&n);
    printf("输入磁道序列：\n");
    for(i=0; i<n; i++)
    {
        scanf("%d",&cidao[i]);
    }
    printf("\n 磁道读取结果：\n");
    for(i=0; i<n; i++)
    {
        printf("%d  ",cidao[i]);//输出读取的磁道的磁道号
    }
    count=n;
    printf("\n           ");
    int choice;
    while(1)
    {
        printf("\n  算法选择：\n");
        printf(" 1、先进先出算法（FIFO）\n");
        printf(" 2、最短时间优先算法（SSTF）\n");
        printf(" 3、扫描算法（SCAN）\n");
        printf(" 4、循环扫描算法（C-SCAN）\n");
        printf(" 5. 退出\n");
        printf("\n");
        printf("请选择：");
        scanf("%d",&choice);
        if(choice>5)
            break;
        switch(choice)//算法选择
        {
        case 1:
            FCFS(cidao,count);//先进先出算法
            printf("\n");
            break;
        case 2:
            SSTF(cidao,count);//最短服务时间优先算法
            printf("\n");
            break;
        case 3:
            SCAN(cidao,count);//扫描算法
            printf("\n");
            break;
        case 4:
            CSCAN(cidao,count);//循环扫描算法
            printf("\n");
            break;
        case 5:
            exit(0);
        }
    }
    return 0;
}
//测试数据
//10 
//80  20  60  140  25  180  110  210  30  120
