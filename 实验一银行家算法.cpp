#include <iostream>
using namespace std; 
int Available[100]; //可利用资源
int Max[50][100];   //最大需求
int Allocation[50][100];  //已分配资源 
int Need[50][100];        //还需资源 
int Request[50][100];     //动态申请资源的需求量 
int Finish[50];
int p[50];
int m,n;
//安全性算法
int Safe()                      
{
    int i,j,l=0;
    int Work[100]; //寻找安全序列时可利用资源的数组
    for (i=0;i<n;i++)
        Work[i]=Available[i];
    for (i=0;i<m;i++)
        Finish[i]=0;
    for (i=0;i<m;i++)
    {
        if (Finish[i]==1)//已进入安全序列的进程不再访问 
        continue;
        else
        {
            for (j=0;j<n;j++)//逐个访问进程所需的每个资源判断是否满足条件 
            {
                if (Need[i][j]>Work[j])
                    break;
            }
            if (j==n)//每个资源都满足条件，这个进程进入安全序列，并把对应的Finish数组赋1 
            {
                Finish[i]=1;
                for(int k=0;k<n;k++)
                    Work[k]+=Allocation[i][k];
                p[l++]=i;
                i=-1;
            }
            else continue;
        }
        if (l==m)//此时所有进程都进入安全序列，判断为安全并输出序列 
        {
            cout<<"系统是安全的"<<'\n';
            cout<<"系统安全序列是:\n";
            for (i=0;i<l;i++)
            {
                cout<<p[i];
                if (i!=l-1)
                    cout<<"-->";
            }
            cout<<'\n';
            return 1;
        }
    }
}
//银行家算法
int main()
{
    int i,j,mi;
    cout<<"输入进程的数目:\n";
    cin>>m;
    cout<<"输入资源的种类:\n";
    cin>>n;
    cout<<"输入每个进程最多所需的各类资源数,按照"<<m<<"x"<<n<<"矩阵输入\n";
    for (i=0;i<m;i++)
        for(j=0;j<n;j++)
            cin>>Max[i][j];
    cout<<"输入每个进程已经分配的各类资源数,按照"<<m<<"x"<<n<<"矩阵输入\n";
    for (i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            cin>>Allocation[i][j];
            Need[i][j]=Max[i][j]-Allocation[i][j];
            if (Need[i][j]<0)
            {
                cout<<"你输入的第"<<i+1<<"个进程所拥有的第"<<j+1<<"个资源错误，请重新输入:\n";
                j--;
                continue;
            }
        }
    }
    cout<<"请输入各个资源现有的数目:\n";
    for (i=0;i<n;i++)
    cin>>Available[i];
    Safe();//此处为第一次对进程进行安全性算法的调用并分配 
    while (1)//此处循环开始为对进程的资源进行动态地申请 
    {
        cout<<"输入要申请的资源的进程号：（第一个进程号为0，第二个进程号为1，依此类推）\n";
        cin>>mi;
        cout<<"输入进程所请求的各个资源的数量\n";
        for (i=0;i<n;i++)
        cin>>Request[mi][i];
        for (i=0;i<n;i++)
        {

            if (Request[mi][i]>Need[mi][i])
            {
                cout<<"所请求资源数超过进程的需求量！\n";
                return 0;
            }
            if (Request[mi][i]>Available[i])
            {
                cout<<"所请求资源数超过系统所有的资源数！\n";
                return 0;
            }
        }
        for (i=0;i<n;i++)
        {
            Available[i]-=Request[mi][i];
            Allocation[mi][i]+=Request[mi][i];
            Need[mi][i]-=Request[mi][i];
        }
        if (Safe())//再次调用安全性算法进行分配 
            cout<<"同意分配请求\n";
        else
        {
            cout<<"申请资源后系统不安全，请求被拒绝。\n";
            for (i=0;i<n;i++)
            {
                Available[i]+=Request[mi][i];
                Allocation[mi][i]-=Request[mi][i];
                Need[mi][i]+=Request[mi][i];
            }
        }
        for (i=0;i<m;i++) 
            Finish[i]=0;
        char Flag;
        cout<<"是否再次请求分配？是请按Y，否请按N\n";
        while (1)
        {
            cin>>Flag;
            if (Flag=='Y'||Flag=='y'||Flag=='N'||Flag=='n')
            break;
            else
            {
                cout<<"请按要求重新输入:\n";
                continue;
            }
        }
        if (Flag=='Y'||Flag=='y')
        continue;
        else break;
    }
}
/*测试数据 
5
4
0 0 1 2
1 7 5 0
2 3 5 6
0 6 5 2
0 6 5 6

0 0 1 2
1 0 0 0
1 3 5 4
0 6 3 2
0 0 1 4

1 5 2 0
*/ 
 
