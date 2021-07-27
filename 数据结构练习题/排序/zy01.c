#include<stdio.h>
#include "time.h" 
void ShellInsert(int a[], int gap, int k, int n)		//(����a������gap����ʼλ��k�������Сn)
{	//�Ե�ǰ������һ��ϣ��������������Ϊgap
	int i, j, tmp;
	for(i = k + gap;i < n;i += gap)
	{
		tmp = a[i];
		j = i - gap;

		while(j >= 0 && a[j] > tmp)
		{
			a[j + gap] = a[j];
			j = j - gap;
		}
		a[j + gap] = tmp;
	}
}

void ShellSort(int a[], int n)
{
	int gap, i;
	for(gap = n / 2;gap > 0;gap /= 2)			//��ȡÿ��������С
	{
		for(i = 0;i < gap;i++)					//���鱻��Ϊgap��
			ShellInsert(a, gap, i, n);
	}
	printf("\n���Ϊ��\n");
	for(i = 0;i < n;i++)
		printf("%d ", a[i]);
}

void fun(char s[]) 
{ 
time_t rawtime; 
struct tm * timeinfo; 
time ( &rawtime ); 
timeinfo = localtime ( &rawtime ); 
printf("%s\n",s); 
printf("%s", asctime (timeinfo) ); 
} 

int main()
{
	int a[10] = {43, 3, 64, 97, 76, 13, 27, 49, 55, 47};
		int i;		int n=10;
	printf("��ʼ����\n");
	for(i=0;i<10;i++)
		printf("%d ",a[i]);

	//	int n = sizeof(a)/sizeof(*a);		//��ȡ���鳤��

ShellSort(a, n);

	getchar();
	fun("���ʵ��ϣ������ʵ��");
	return 0;
}
