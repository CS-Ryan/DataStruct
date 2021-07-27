#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct BSTNode//���ݽڵ㶨��
{
	int data;
	struct BSTNode *lchild,*rchild;
};
void InsertBST(struct BSTNode **bst, int k)//����������-������
{
	if(bst==NULL)//���ԭ��Ϊ��
	{
		*bst=(struct BSTNode *)malloc(sizeof(struct BSTNode));
		(*bst)->data=k;
		(*bst)->lchild=NULL;
		(*bst)->rchild=NULL;
	}
	else//���ԭ����Ϊ��
	{
		struct BSTNode *s=*bst,*pre=NULL;
		while(s)//ѭ���Ҳ�����λ��
		{
			pre=s;//��¼�����
			if(k<s->data)
				s=s->lchild;
			else if(k>s->data)
				s=s->rchild;
			else//����ҵ����Ԫ��
				break;
		}
		if(!s)//���û�ҵ���ͬ��㣬�ҵ�����λ��
		{
		struct BSTNode *p=(struct BSTNode *)malloc(sizeof(struct BSTNode));
			p->data=k;
			p->lchild=NULL;
			p->rchild=NULL;
			if(k<pre->data)
				pre->lchild=p;
			else
				pre->rchild=p;
		}
	}
}
struct BSTNode *CreateBST(int a[],int n)//��������a��������������
{
	int i;
	struct BSTNode *root=(struct BSTNode *)malloc(sizeof(struct BSTNode)),*pre=NULL,*p=NULL;
	root->data=a[0];
	root->lchild=NULL;
	root->rchild=NULL;
	for(i=1;i<=n-1;i++)
	{
		p=root;
		while(p)
		{
			pre=p;//һֱָ��p���ĸ��ڵ�
			if(a[i]<p->data)
				p=p->lchild;
			else if(a[i]>p->data)
				p=p->rchild;
			else
				break;//�ҵ���ȵ�break��������ǰ����ѭ��

		}
		if(!p)//���p���ڿգ�û�ҵ���Ƚڵ�
		{
			p=(struct BSTNode *)malloc(sizeof(struct BSTNode));
			p->data=a[i];
			p->lchild=NULL;
			p->rchild=NULL;//ͨ��pre��p����pre�����ӻ��Һ���λ��
			if(a[i]<pre->data)//����λ��
				pre->lchild=p;
			else//�Һ���λ��
				pre->rchild=p;
		}
	}
	return root;
}

void InOrder(struct BSTNode *root)//�����������������
{
	if(root!=NULL)
	{
		InOrder(root->lchild);
		printf(" %d ",root->data);
		InOrder(root->rchild);
	}
}
void FiOrder(struct BSTNode *root)//�����������������
{
	if(root!=NULL)
	{
		printf(" %d ",root->data);
		FiOrder(root->lchild);
		FiOrder(root->rchild);
	}
}
void FreeBST(struct BSTNode *root)//�ͷŶ������ռ�
{
	if(root!=NULL)
	{
		FreeBST(root->lchild);
		FreeBST(root->rchild);
		free(root);
	}
}
struct BSTNode *SearchBST(struct BSTNode *bst,int key)//�ڶ����������в���ָ���ڵ�
{
	struct BSTNode *p=bst;
	while(p)
	{
		if(key==p->data)
			return p;//�ҵ�ָ��ֵ��㣬���ظý��ָ��
		else if(key<p->data)
			p=p->lchild;
		else
			p=p->rchild;
	}
	return NULL;//����ʧ��
}
void DeleteBST(struct BSTNode **bst,int key)//�ڶ�����������ɾ��ָ�����
{
	struct BSTNode *p=*bst,*pre=*bst,*s=NULL,*spre=NULL;
	while(p)//ѭ����ֵΪkey�Ľ��
	{
		if(key==p->data)//�ҵ����ֵ����key�Ľ��
			break;//��ǰ������p���ҵ����ĵ�ַ
		else if(key<p->data)
		{
			pre=p;//preһֱָ��p�ĸ��ڵ�
			p=p->lchild;
		}
		else
		{
			pre=p;//preһֱָ��p�ĸ��ڵ�
			p=p->rchild;
		}
	}
	if(p)//����ҵ�key���
	{
		if(p->lchild==NULL&&p->rchild==NULL)//�����Ҷ�ӽ��
		{
			if(p==*bst)//���ֻ��һ�����
				*bst=NULL;
			else if(p==pre->lchild)
				pre->lchild=NULL;
			else if(p==pre->rchild)
				pre->rchild=NULL;
		}
		else if(p->lchild!=NULL&&p->rchild==NULL)//���p����������ն���������Ϊ��
		{
			if(p==*bst)//���p���������
			*bst=p->lchild;
		else if(p==pre->lchild)//���p���Ǹ���㣬���Ǹ�����������
			pre->lchild=p->rchild;
		else if(p==pre->rchild)//���p���Ǹ���㣬���Ǹ�����������
			pre->rchild=p->lchild;
		}
		else if((p->lchild==NULL)&&(p->rchild!=NULL))//���p����������ն�����������
		{
			if(p==*bst)//���p���������
				*bst=p->rchild;
			else if(p==pre->lchild)//���p���Ǹ���㣬���Ǹ�����������
				pre->lchild=p->rchild;
			else if(p==pre->rchild)//���p���Ǹ���㣬���Ǹ�����������
				pre->rchild=p->rchild;
		}
		else//���p�����������������
		{
			s=p->lchild;
			if(s->rchild==NULL)
			{
				if(p==*bst)
					*bst=s;
				else if(p==pre->lchild)
					pre->lchild=s;
				else if(p==pre->rchild)
					pre->rchild=s;
				s->rchild=p->rchild;
			}
			else
			{
				while(s->rchild)
				{
					spre=s;
					s=s->rchild;
				}
				spre->rchild=s->lchild;
				if(p==*bst)
					*bst=s;
				else if(p==pre->lchild)
					pre->lchild=s;
				else if(p==pre->rchild)
					pre->rchild=s;
				s->lchild=p->lchild;
				s->rchild=p->rchild;
			}
		}
		free(p);
	}
}
int jdgs=0,zbjcs=0;
void qasl(struct BSTNode *t,int jdcs)
{
	if(t)
	{
		jdgs++;
		zbjcs=zbjcs+jdcs;
		qasl(t->lchild,jdcs+1);
		qasl(t->rchild,jdcs+1);
	}
}
void funp(char s[])
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}
void main()
{
	//int a[12]={7,6,9,8,12,10},h,hc;//RR-��
	int a[12]={5,2,7,6,9,12,1,3,4,8,10,11};//RR�Ǹ�
	//int a[12]=[7,6,19,11,22,12],h,hc;//RL-��
	//int a[12]={5,3,2,4,1,7,6,19,11,12,22},h,hc;//RL-��
	//int a[12]={27,19,11,22,12,32},h,hc;//LL-��
	//int a[12]={50,60,27,19,11,22,12,32},h,hc;//LL-�Ǹ�
	//int a[12]={27,19,11,22,32,23},h,hc;//LR-��
	//int a[12]={50,60,27,19,11,22,32,23},h,hc;//LR-�Ǹ�
	struct BSTNode *bst=NULL,*p=NULL;
	bst=CreateBST(a,12);
	InOrder(bst);
	printf("\n");
	InsertBST(&bst,16);
	InOrder(bst);
	printf("\n");
	DeleteBST(&bst,5);
	InOrder(bst);
	p=SearchBST(bst,16);
	if(p)
		printf("\n�ҵ���! \n");
	else
		printf("\nû�ҵ�! \n");
	DeleteBST(&bst,5);
	InOrder(bst);
	qasl(bst,1);
	printf("\nASL:%d/%d\n",zbjcs,jdgs);
	FreeBST(bst);
	funp("�������������Ĵ��������롢ɾ������ʵ��");
	}












































































