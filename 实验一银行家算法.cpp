#include <iostream>
using namespace std; 
int Available[100]; //��������Դ
int Max[50][100];   //�������
int Allocation[50][100];  //�ѷ�����Դ 
int Need[50][100];        //������Դ 
int Request[50][100];     //��̬������Դ�������� 
int Finish[50];
int p[50];
int m,n;
//��ȫ���㷨
int Safe()                      
{
    int i,j,l=0;
    int Work[100]; //Ѱ�Ұ�ȫ����ʱ��������Դ������
    for (i=0;i<n;i++)
        Work[i]=Available[i];
    for (i=0;i<m;i++)
        Finish[i]=0;
    for (i=0;i<m;i++)
    {
        if (Finish[i]==1)//�ѽ��밲ȫ���еĽ��̲��ٷ��� 
        continue;
        else
        {
            for (j=0;j<n;j++)//������ʽ��������ÿ����Դ�ж��Ƿ��������� 
            {
                if (Need[i][j]>Work[j])
                    break;
            }
            if (j==n)//ÿ����Դ������������������̽��밲ȫ���У����Ѷ�Ӧ��Finish���鸳1 
            {
                Finish[i]=1;
                for(int k=0;k<n;k++)
                    Work[k]+=Allocation[i][k];
                p[l++]=i;
                i=-1;
            }
            else continue;
        }
        if (l==m)//��ʱ���н��̶����밲ȫ���У��ж�Ϊ��ȫ��������� 
        {
            cout<<"ϵͳ�ǰ�ȫ��"<<'\n';
            cout<<"ϵͳ��ȫ������:\n";
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
//���м��㷨
int main()
{
    int i,j,mi;
    cout<<"������̵���Ŀ:\n";
    cin>>m;
    cout<<"������Դ������:\n";
    cin>>n;
    cout<<"����ÿ�������������ĸ�����Դ��,����"<<m<<"x"<<n<<"��������\n";
    for (i=0;i<m;i++)
        for(j=0;j<n;j++)
            cin>>Max[i][j];
    cout<<"����ÿ�������Ѿ�����ĸ�����Դ��,����"<<m<<"x"<<n<<"��������\n";
    for (i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            cin>>Allocation[i][j];
            Need[i][j]=Max[i][j]-Allocation[i][j];
            if (Need[i][j]<0)
            {
                cout<<"������ĵ�"<<i+1<<"��������ӵ�еĵ�"<<j+1<<"����Դ��������������:\n";
                j--;
                continue;
            }
        }
    }
    cout<<"�����������Դ���е���Ŀ:\n";
    for (i=0;i<n;i++)
    cin>>Available[i];
    Safe();//�˴�Ϊ��һ�ζԽ��̽��а�ȫ���㷨�ĵ��ò����� 
    while (1)//�˴�ѭ����ʼΪ�Խ��̵���Դ���ж�̬������ 
    {
        cout<<"����Ҫ�������Դ�Ľ��̺ţ�����һ�����̺�Ϊ0���ڶ������̺�Ϊ1���������ƣ�\n";
        cin>>mi;
        cout<<"�������������ĸ�����Դ������\n";
        for (i=0;i<n;i++)
        cin>>Request[mi][i];
        for (i=0;i<n;i++)
        {

            if (Request[mi][i]>Need[mi][i])
            {
                cout<<"��������Դ���������̵���������\n";
                return 0;
            }
            if (Request[mi][i]>Available[i])
            {
                cout<<"��������Դ������ϵͳ���е���Դ����\n";
                return 0;
            }
        }
        for (i=0;i<n;i++)
        {
            Available[i]-=Request[mi][i];
            Allocation[mi][i]+=Request[mi][i];
            Need[mi][i]-=Request[mi][i];
        }
        if (Safe())//�ٴε��ð�ȫ���㷨���з��� 
            cout<<"ͬ���������\n";
        else
        {
            cout<<"������Դ��ϵͳ����ȫ�����󱻾ܾ���\n";
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
        cout<<"�Ƿ��ٴ�������䣿���밴Y�����밴N\n";
        while (1)
        {
            cin>>Flag;
            if (Flag=='Y'||Flag=='y'||Flag=='N'||Flag=='n')
            break;
            else
            {
                cout<<"�밴Ҫ����������:\n";
                continue;
            }
        }
        if (Flag=='Y'||Flag=='y')
        continue;
        else break;
    }
}
/*�������� 
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
 
