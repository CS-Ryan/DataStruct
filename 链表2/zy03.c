#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
typedef struct xs{
	int data;
	int *next;
}link;

link* init();//��ʼ��
void initlist(link *hd,int n);//��ʼ����ֵ
void insert(link *hd,int n,int c);//����
link* search(link *hd,int n);//����
link* dele(link *hd,int n);//ɾ��
int dele1(link *hd,int n);
void display(link *hd);//������ʾ
void deleall(link *hd);//ɾ����������
void clear(link *hd,int n);
int main()
{	
	int n,c;
	link *hd=NULL,*w=NULL;
	hd=init();w=init();
	printf("�������ʼ����1�ĳ���\n");
	scanf("%d",&n);
	initlist(hd,n);
				printf("�������ʼ����2�ĳ���\n");
				scanf("%d",&c);
				initlist(w,c);
	insert(hd,w,n,c);
	printf("������Ϊ��\n");clear(hd,n+c);display(hd);
	printf("��ʼ�������\n");
	deleall(hd);
	return 0;
}
void clear(link *hd,int n)
{
	int i,j;
	link *p,*w,*e;
	p=init();
	for(i=1;i<n;i++)
	{
		w=search(hd,i);
		for(j=i+1;j<=n;j++)
		{	e=search(hd,j);
	
			if(w->data>e->data)
			{	
				p->data=w->data;
				w->data=e->data;
				e->data=p->data;
			//	if(f==-1)
			//		break;
		//	j--;n--;
			}
		}
	}
}
void insert(link *hd,link *w,int n,int c)//n=����1�ĳ��ȣ�c=����2�ĳ���
{
	int i=0,b=0;
	link *p,*e;
	p=search(hd,n-1);
while(i<c)
{
	e=dele(w,1);
	if(e==NULL)
	{	break;
	}
	e->next=p->next;
	p->next=e;
	i++;
		
}
}
void deleall(link *hd)
{
	link *p,*q;
	p=hd->next;
	while(p)
	{
		q=p->next;
		free(p);
		p=q;
	}
	hd->next=NULL;
	display(hd);

}
void display(link *hd)
{
	link *p=hd;
	printf("���������");
	while(p->next)
	{
		p=p->next;
		printf("%d ",p->data);
	}
	printf("\n");
}
int dele1(link *hd,int n)
{
	
	link *q,*p;
	p=search(hd,n-1);
	if(!p)
		return -1;
	q=p->next;
	p->next=q->next;
	free(q);
	return 0;
}
link* dele(link *hd,int n)
{
	link *q,*p;
	p=search(hd,n-1);
	if(!p)
		return NULL;
	q=p->next;
	p->next=q->next;
	return q;

}
link* search(link *hd,int n)
{
	int i=0;
	link *p;
	p=hd;
	while(p&&i<n)
	{	p=p->next;
		i++;
	}
	if(!p||i>n)
		return NULL;
	return p;

}
void initlist(link *hd,int n)
{
	int i;
	link *p;
		for(i=n;i>0;i--)
	{
		p=(link *)malloc(sizeof(link));
		p->data=i;
		p->next=hd->next;
		hd->next=p;
	}
		display(hd);
}
link* init()
{
	link *hd=(link *)malloc(sizeof(link));
	hd->next=NULL;
	return  hd;
}
