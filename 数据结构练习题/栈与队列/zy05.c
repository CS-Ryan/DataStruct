#include<stdio.h>//����ȳ�
#include<stdlib.h>
#define maxsize 10
typedef struct xs
{
	int front,rear;
	int data[maxsize];
}queue1;
int main()
{	int n,i;
	queue1 *p;
	p=(queue1 *)malloc(sizeof(queue1));p->front=0;p->rear=0;
	printf("������Ԫ�ظ���\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)//������
	{
		if((p->rear+1)%maxsize==p->front){printf("����������\n");break;	}
		p->data[p->rear]=i;
		p->rear=(p->rear+1)%maxsize;
	}
	printf("���еĳ���Ϊ��%d\n",(maxsize-p->front+p->rear)%maxsize);
	printf("�����еĵ�һ��Ԫ�أ�\n");
	printf("%d\n-------\n",p->data[p->front]);
	p->front=(p->front+1)%maxsize;
	printf("������գ�\n");
	while(p->front!=p->rear)//�������
	{
		printf("%d ",p->data[p->front]);
		p->front=(p->front+1)%maxsize;
	}
	printf("\n");
	printf("�ռ��ͷţ�\n");
	free(p);
}