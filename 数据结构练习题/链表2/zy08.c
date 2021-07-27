#include<stdio.h>
#include<malloc.h>
#include <math.h>
typedef struct xs{
	double data;
	int *next;
}link;

link* init();//��ʼ��
void initlist(link *hd,int n);//��ʼ����ֵ
void insert(link *hd,link *w,int n,int c);//����
link* search(link *hd,int n);//����
link* dele(link *hd,int n);//ɾ��
void dele1(link *hd,int n);
void display(link *hd);//������ʾ
void deleall(link *hd);//ɾ����������
void clear(link *hd,int n);
void clear1(link *hd,int n);
void sum(link *hd);
int main()
{	
	int n,c,i;
	link *hd=NULL,*w=NULL;
	hd=init();w=init();
	printf("�������ʼ����1�ĳ���\n");
	scanf("%d",&n);
	initlist(hd,n);
				printf("�������ʼ����2�ĳ���\n");
				scanf("%d",&c);
				initlist(w,c);
	printf("�����Ϻϲ���\n");
	insert(hd,w,n,c);
	sum(hd);
		printf("��ʼ�������\n");
	deleall(hd);deleall(w);
//	display(h);

	return 0;
}
void sum(link *hd)
{double s=0,t=0;	link *p;p=hd;
	
	
	while(p->next)
	{	
		p=p->next;t=p->data;
		s=s+t;
	}
	printf("��Ϊ��%0.2lf\n",s);
}
void clear1(link *hd,int n)
{
	int i,j;
	link *w,*e;
	for(i=1;i<n;i++)
	{
		w=search(hd,i);
		for(j=i+1;j<=n;j++)
		{	e=search(hd,j);
		//	printf("li\n");
			if(w->data==e->data)
			{
			//	printf("pu\n");
				dele1(hd,j);
				n--;j--;
			}
		}
	}
}
void clear(link *hd,int n)
{
	int i,j,t=0;
	link *w,*e;
	for(i=1;i<n;i++)
	{
		w=search(hd,i);t=0;
		for(j=i+1;j<=n;j++)
		{	e=search(hd,j);
		//	printf("li\n");
			if(w->data==e->data)
			{
			//	printf("pu\n");
				dele1(hd,j);
				n--;j--;
				t=t+1;//
			
			}
			
		}
		if(t>=1)//
			{	dele1(hd,i);
				n--;i--;
			}//
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
		printf("%0.2lf ",p->data);
	}
	printf("\n");
}
void dele1(link *hd,int n)
{
	
	link *q,*p;
	p=search(hd,n-1);	
	q=p->next;
	p->next=q->next;
	free(q);
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
	double y,u,b;
	int i,j;
	link *p;
		for(i=1;i<n+1;i++)
	{
		p=(link *)malloc(sizeof(link));
		printf("�������%d������ϵ����ָ��",i);
		scanf("%lf %lf",&y,&u);
		b=pow(y,u);
		p->data=b;
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
