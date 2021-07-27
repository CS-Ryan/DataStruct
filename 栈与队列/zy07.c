#include<stdio.h>
#include<stdlib.h>
typedef struct xs
{
	int data;
	struct xs *next;
}node,*link;
typedef struct 
{
	link front,rear;
}queue1;
void initqueue1(queue1 *p)
{
	p->front=p->rear=(link)malloc(sizeof(node));
	p->front->next=NULL;	
}
void inqueue1(queue1 *p)//����
{
	node *s;int n,i;
	printf("�������Ԫ�ظ���:\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		s=(node *)malloc(sizeof(node));
		s->data=i;s->next=NULL;
		p->rear->next=s;
		p->rear=s;
	}
	printf("������ϣ�\n");
}
void visit(queue1 *p)
{
	node *s;
		s=p->front->next;
	while(s)
	{		printf("%d ",s->data);
			s=s->next;
	}
	
}
int outqueue1(queue1 *p)
{	
	node *s;
	if(p->front==p->rear)return 0;//�����ѿ�
	printf("��ʼ���Ӳ���;\n");
	s=p->front->next;
	p->front->next=s->next;
	if(s==p->rear){p->rear=p->front;}
	printf("���еĵ�һ��Ԫ��%d�ѳ���\n",s->data);
	free(s);
	printf("���ӽ��:\n");
	visit(p);
	return 1;
}
void clearqueue1(queue1 *p)
{node *s;
	while(p->front!=p->rear)
	{
		s=p->front->next;
		p->front->next=s->next;
		if(s==p->rear){p->rear=p->front;}
		free(s);
	}
	printf("����������գ�\n");
	visit(p);
}
void lenght(queue1 *p)
{	node *s;int i=0;s=p->front->next;
	while(s)
	{
		i++;
		s=s->next;
	}
	printf("�����г���Ϊ��%d\n",i);
}
int main()
{
	queue1 p;int i;
	initqueue1(&p);
	inqueue1(&p);//����	
	lenght(&p);
	visit(&p);//����
	i=outqueue1(&p);//����
	printf("\n");
	if(i==0)printf("�����ѿգ�\n");
	clearqueue1(&p);//���
	return 0;
}