#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define maxsize 20
void fun(char s[])
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}
int main()
{	int i,n,x,a[maxsize];
//int high,mid,low;
printf("������n������\n");
scanf("%d",&x);//	high=x;low=0;
	for(i=1;i<x+1;i++)
	{
		scanf("%d",&a[i]);	
	}
	printf("����������Ҫ���ҵ�����\n");
	scanf("%d",&n);	a[0]=n;i=n;
		while(a[i]!=n)
		{
			i--;
		}
		if(i==0)printf("����ʧ��\n");else
		{	printf("���ҳɹ�!\n");printf("��Ԫ���������±�Ϊ%d\n",i);}
		fun("�۰�����㷨");
	
}