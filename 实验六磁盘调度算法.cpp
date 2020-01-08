#include <stdio.h>
#include <algorithm>
#include <string>
#define maxsize 1000 //�������������
using namespace std;
//�Ƚ��ȳ������㷨
void FCFS(int array[],int m)
{
    int sum=0,j,i,now;
    float average;
    printf("\n �����뵱ǰ�Ĵŵ��ţ�");
    scanf("%d",&now);
    printf("\n ���Ƚ��:  ");
    printf("%d ",now);
    for(i=0; i<m; i++) 
		printf("%d ",array[i]);
    sum=abs(now-array[0]);
    for(j=1; j<m; j++) sum+=abs(array[j]-array[j-1]); //�ۼ��ܵ��ƶ�����
    average=(float)sum/m;//����ƽ��Ѱ������
    printf("\n �ƶ����ܵ����� %d \n",sum);
    printf(" ƽ��Ѱ�����ȣ� %f \n",average);
}
 
//���ʱ�����ȵ����㷨
void SSTF(int array[],int m)
{
    int temp;
    int k=1;
    int now,l,r;
    int i,j,sum=0;
    float avg;
    for(i=0; i<m; i++)
    {
        for(j=i+1; j<m; j++) //�Դŵ��Ž��д�С��������
        {
            if(array[i]>array[j])//���ŵ���֮��Ƚ�
            {
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }
    }
    for( i=0; i<m; i++) //��������Ĵŵ�������
        printf("%d  ",array[i]);
    printf("\n �����뵱ǰ�Ĵŵ��ţ�");
    scanf("%d",&now);
    printf("\n SSTF���Ƚ��:  ");
    if(array[m-1]<=now)//�ж���������������Ƿ�С�ڵ�ǰ�ŵ���
    {
        for(i=m-1; i>=0; i--) //������ŵ��ŴӴ�С���
            printf("%d  ",array[i]);
        sum=now-array[0];//�����ƶ�����
    }
    else if(array[0]>=now)//�ж���������������Ƿ񶼴��ڵ�ǰ�ŵ���
    {
        for(i=0; i<m; i++) //���ŵ��Ŵ�С�������
            printf("%d  ",array[i]);
        sum=array[m-1]-now;//�����ƶ�����
    }
    else
    {
        while(array[k]<now)//��һ�Ƚ���ȷ��Kֵ
        {
            k++;
        }
        l=k-1;
        r=k;
        //ȷ����ǰ�ŵ������ŵ������е�λ��
        while((l>=0)&&(r<m))
        {
            if((now-array[l])<=(array[r]-now))//�ж���̾���
            {
                printf("%d  ",array[l]);
                sum+=now-array[l];//�����ƶ�����
                now=array[l];
                l=l-1;
            }
            else
            {
                printf("%d  ",array[r]);
                sum+=array[r]-now;//�����ƶ�����
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
            sum+=array[m-1]-array[0];//�����ƶ�����
        }
        else
        {
            for(j=l; j>=0; j--)
            {
                printf("%d  ",array[j]);
            }
            sum+=array[m-1]-array[0];//�����ƶ�����
        }
    }
    avg=(float)sum/m;
    printf("\n �ƶ����ܵ����� %d \n",sum);
    printf(" ƽ��Ѱ�����ȣ� %f \n",avg);
}
// SCAN
void SCAN(int array[], int m)
{	int now, direction;
    printf("\n �����뵱ǰ�Ĵŵ��ţ� ");
    scanf("%d",&now);
    printf("\n ��ѡ���ͷ�ƶ�����1���⣬2����\n");
    scanf("%d", &direction);
    std::sort(array, array + m);
    int sum = 0;
    float avg;
    printf("\n ���Ƚ��: ");
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
        avg=(float)sum/m;//����ƽ��Ѱ������
        printf("\n �ƶ����ܵ����� %d \n",sum);
        printf(" ƽ��Ѱ�����ȣ� %f \n",avg);
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
        avg=(float)sum/m;//����ƽ��Ѱ������
        printf("\n �ƶ����ܵ����� %d \n",sum);
        printf(" ƽ��Ѱ�����ȣ� %f \n",avg);
    }
}

void CSCAN(int array[], int m)
{
    int now,direction;
    printf("\n �����뵱ǰ�Ĵŵ��ţ� ");
    scanf("%d",&now);
    printf("\n ��ѡ���ͷ�ƶ�����1���⣬2����\n");
    scanf("%d", &direction);
    sort(array, array + m);
    int sum = 0;
    float avg;
    printf("\n ���Ƚ��: ");
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
        avg=(float)sum/m;//����ƽ��Ѱ������
        printf("\n �ƶ����ܵ����� %d \n",sum);
        printf(" ƽ��Ѱ�����ȣ� %f \n",avg);
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
        avg=(float)sum/m;//����ƽ��Ѱ������
        printf("\n �ƶ����ܵ����� %d \n",sum);
        printf(" ƽ��Ѱ�����ȣ� %f \n",avg);
    }
}
 
// ��������
int main()
{	int count;
    int cidao[maxsize];//����ŵ�������
    int i=0;
    int n;
    printf("���̵����㷨ģ��\n");
    printf("����ŵ�������\n");
    scanf("%d",&n);
    printf("����ŵ����У�\n");
    for(i=0; i<n; i++)
    {
        scanf("%d",&cidao[i]);
    }
    printf("\n �ŵ���ȡ�����\n");
    for(i=0; i<n; i++)
    {
        printf("%d  ",cidao[i]);//�����ȡ�Ĵŵ��Ĵŵ���
    }
    count=n;
    printf("\n           ");
    int choice;
    while(1)
    {
        printf("\n  �㷨ѡ��\n");
        printf(" 1���Ƚ��ȳ��㷨��FIFO��\n");
        printf(" 2�����ʱ�������㷨��SSTF��\n");
        printf(" 3��ɨ���㷨��SCAN��\n");
        printf(" 4��ѭ��ɨ���㷨��C-SCAN��\n");
        printf(" 5. �˳�\n");
        printf("\n");
        printf("��ѡ��");
        scanf("%d",&choice);
        if(choice>5)
            break;
        switch(choice)//�㷨ѡ��
        {
        case 1:
            FCFS(cidao,count);//�Ƚ��ȳ��㷨
            printf("\n");
            break;
        case 2:
            SSTF(cidao,count);//��̷���ʱ�������㷨
            printf("\n");
            break;
        case 3:
            SCAN(cidao,count);//ɨ���㷨
            printf("\n");
            break;
        case 4:
            CSCAN(cidao,count);//ѭ��ɨ���㷨
            printf("\n");
            break;
        case 5:
            exit(0);
        }
    }
    return 0;
}
//��������
//10 
//80  20  60  140  25  180  110  210  30  120
