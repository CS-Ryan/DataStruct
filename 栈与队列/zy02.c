#include<stdio.h>//����ȳ�
#define maxsize 10
typedef struct xs
{
	int top;
	int data[maxsize];
}stack1;
void option(stack1 *p,int x,int y)//x��Ҫ��������֣�y���������� 
{
	int i,j;
	while(j!=0)
	{	i=x%y;
		j=x/y;x=j;
		p->top=p->top+1;
		p->data[p->top]=i;
	
	}printf("���Ӧ��%d������Ϊ��",y);printf("\n");
	while(p->top!=-1)
	{
		printf("%d",p->data[p->top]);
		p->top=p->top-1;
	}
	printf("\n");
}
int main()
{
	stack1 p;int n,j,i;
	p.top=-1;
	printf("������һ��ʮ������������");
	scanf("%d",&n);
	option(&p,n,2);
	option(&p,n,8);
	option(&p,n,16);
	return 0;

}