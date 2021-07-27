#include "stdio.h"
#include <time.h>
int c=0;//ȫ�ֱ��������ڼ�¼��������
void swap(int a[],int i,int j)//����a[i]��a[j]��ֵ������
{
	int temp;
	temp=a[i];
	a[i]=a[j];
	a[j]=temp;
	c++;
}
void fun(char s[])
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}
void heapadjust(int a[],int m,int n)//����a[m]��a[n]Ϊ�����
{
	int i;
	for(i=2*m;i<=n;i*=2)
	{
		if(i+1>n)//���mû���Һ���,ֻ������,i+1Ϊm���Һ���
		{
			if(a[i]>a[m])//������Ӵ��ڸ����������Ӻ͸�
			{
				swap(a,i,m);
				m=i;//Ϊ��������������׼��
			}
			else 
				break;
		}
		else if(i+1<=n)//���m�� ������������,i+1Ϊm���Һ���
		{
			if(a[i+1]>a[i])//����Һ��Ӵ�������
			{
				if(a[i+1]>a[m])//�������Һ��Ӵ��ڸ������������Һ���
				{
					swap(a,i+1,m);
					i++;
				    m=i;
				}
				else//���������ĺ��Ӷ�С�ڵ��ڸ�����С�ĸ�С�ڸ����������õ���
					break; 
			}
			else//������Ӵ��ڵ����Һ���
			{
				if(a[i]>a[m])//������(����ȵ�)���Ӵ��ڸ���������������
				{
					swap(a,i,m);
					m=i;//Ϊ��������������׼��
				}
				else
					break; 
			}
		}
	}
}
					
void crtheap(int a[],int n)//��ʼ������һ���󶥶�
{
	int i;
	for(i=n/2;i>=1;i--)//n/2Ϊ���һ��˫�׽ڵ㣬������ǰ�����󶥶�
	{
		heapadjust(a,i,n);
	}
}
void heapsort(int a[],int n)
{
	int i;
	crtheap(a,n);//��һ�ε���Ϊ�����
	for(i=n;i>=2;i--)//n-1�˽���/����
	{
		swap(a,1,i);//���Ѷ������(��һ����)���ŵ�a[i]λ��
		heapadjust(a,1,i-1);//��ʣ�µ�a[1]��a[i-1],�ٴε���Ϊ�����
	}
}



void main()
{
	int i;

	int a[11]={-1,75,54,22,63,04,33,97,16,75,44};//Ϊ���������Һ��Ӵ���a[0]δʹ��
	heapsort(a,10);

	for(i=1;i<=10;i++)
		printf(" %d",a[i]);	printf("��������%d��\n",c);
	printf("\n");
	fun("���������ʵ��");
}
