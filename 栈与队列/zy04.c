#include<stdio.h>//�ݹ����Թ� 
#include<stdlib.h>
#define maxsize 20 
/*�Թ����壺{1,1,1,1,1,1}	a0
������������{1,2,2,3,1,1}	a1,(1,1)~(4,4)
������������{1,0,1,1,1,1}	a2
������������{1,0,0,0,0,1}	a3
������������{1,0,0,0,0,1}	a4
������������{1,1,1,1,1,1}	a5
*/
typedef struct xs
{
	int top;
	int data1[maxsize];//�洢i��
	int data2[maxsize];//�洢j��
}stack1;
int a[6][6]={{1,1,1,1,1,1},{1,0,0,0,1,1},{1,0,1,1,1,1},{1,0,0,0,0,1},{1,0,0,0,0,1},{1,1,1,1,1,1}};
float option2(int a[6][6],int i,int j)
{	float x,y,z,c;	
if(a[i][j]!=0)return -1;else if(a[4][4]==2)return 0;//�ݹ����,����޷��ߣ��ͳ�ջ
		a[i][j]=2;

	x=option2(a,i,j+1);//��

	y=option2(a,i+1,j);//��

	z=option2(a,i,j-1);//��

	c=option2(a,i-1,j);//��
	if(x+y+z+c==-4){a[i][j]=3;return -1;}//������ܶ��޷��ߣ��ͳ�ջ
	return 0;

}
int main()
{	int i,j;float x;
	printf("�Թ�����:\n");
	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
		printf("%d ",a[i][j]);printf("\n");
	}
	printf("\n--------------\n");i=1;j=1;
	x=option2(a,i,j);printf("���н��:\n");
	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
		printf("%d ",a[i][j]);printf("\n");
	}
	printf("�ѵ��\n");
	return 0;
}