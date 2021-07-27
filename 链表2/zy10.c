#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
typedef struct xs{
	int data;
	int *next;
}link;

link* init();//��ʼ��
void initlist(link *hd,int n);//��ʼ����ֵ
void insert(link *hd,link *w,link *h,int n,int c);//����
link* search(link *hd,int n);//����
link* dele(link *hd,int n);//ɾ��
int dele1(link *hd,int n);
void display(link *hd);//������ʾ
void deleall(link *hd);//ɾ����������
void clear(link *hd,link *h,int n,int c);
void option2(link *hd,int *k);
int main()
{	
	int n,c,k=0;
	link *hd=NULL,*w=NULL,*h=NULL;
	hd=init();w=init();h=init();
	printf("�������ʼlb�ĳ���\n");
	scanf("%d",&n);
	initlist(hd,n);
				printf("�������ʼla�ĳ���\n");
				scanf("%d",&c);
				initlist(w,c);
	printf("�����Ϻϲ���\n");
	insert(hd,w,h,n,c); 
		printf("����Ϊ��\n");
	clear(hd,h,n,c); display(h);
	option2(h,&k);
	if(k==c)
		printf("la��lb���Ӽ�\n");
	else printf("la����lb���Ӽ�\n");

	printf("��ʼ�������\n");
	deleall(h);deleall(hd);
	return 0;
}
void option2(link *hd,int *k)
{
	link *p=hd;
	int i=0; 
	while(p->next)
	{
		p=p->next; i=i+1;
	}
//	p->next=NULL;
	*k=i;
}
void clear(link *hd,link *h,int n,int c)
{
	int i,j;
	link *p,*w,*e;
	for(i=1;i<=n;i++)
	{
		w=search(hd,i);
		for(j=n+1;j<=n+c;j++)
		{	e=search(hd,j);
	
			if(w->data==e->data)
			{
				p=(link *)malloc(sizeof(link));
				p->data=e->data;
				p->next=h->next;
				h->next=p;
			}
		}
	}
}
void insert(link *hd,link *w,link *h,int n,int c)//n=����1�ĳ��ȣ�c=����2�ĳ���
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
	display(hd);
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
		for(i=0;i<n;i++)
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
