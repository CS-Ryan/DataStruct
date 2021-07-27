#include "stdio.h" 
#include "stdlib.h"
#include <time.h>
#define VEXNUM 6
#define ARCNUM 10
#define INF 9999    //�����
struct Graph        //ͨ��ͼ�ζ��壬���ڴ���ͼ�ε��ڽӾ�����ڽӱ�-ȫ�ֱ���
{
	int vexnum,arcnum,kind;//��������������ͼ���ͣ�1234-����ͼ������ͼ����������������
	char vexs[VEXNUM+1];   //�����ַ�����
	int arcs[ARCNUM*3];     //����ֹ���±꼰Ȩֵ����
} graph={5,7,4,"ABCDEF",{0,4,100,0,3,30,0,1,10,1,2,50,2,4,10,3,4,60,3,2,20}};
//6�����㡢10���ߡ�����������������ΪABCDEF��A-B:6/A-C:1/A-D:5/B-C:5/B-E:3/C-E:6/C-F:4/C-D:5/D-F:2/E-F:6
struct MGraph_Mat      //ͼ���ڽӾ���洢���ݶ���
{
	int vexnum,arcnum;//������������
	char vexs[VEXNUM];//��������
	int arcs[VEXNUM][VEXNUM];//�ڽӾ���
	int kind;                //ͼ����
};
void create_Mat(struct MGraph_Mat *g)
{
	int i,j;
	g->vexnum=graph.vexnum;//������
	g->arcnum=graph.arcnum;//����
	g->kind=graph.kind;      //ͼ���ͣ�1234-����ͼ������ͼ����������������
	for(i=0;i<=g->vexnum-1;i++)
	  g->vexs[i]=graph.vexs[i];
    for(i=1;i<=g->vexnum;i++)
	{
		for(j=1;j<=g->vexnum;j++)
		{
			if(g->kind==1||g->kind==2)
				g->arcs[i-1][j-1]=0;
			else
				g->arcs[i-1][j-1]=INF;
		}
	}
	for(i=0;i<=g->arcnum-1;i++)
	{
		if(g->kind==1)
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=1;
			g->arcs[graph.arcs[i*3+1]][graph.arcs[i*3]]=1;
		}
		else if(g->kind==2)
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=1;
		}
		else if(g->kind==3)
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=graph.arcs[i*3+2];
			g->arcs[graph.arcs[i*3+1]][graph.arcs[i*3]]=graph.arcs[i*3+2];
		}
		else if(g->kind==4)
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=graph.arcs[i*3+2];
		}
	}
}
void print_Mat(struct MGraph_Mat g)     //��ʾ�ڽӾ���
{
	int i,j;
	printf("  ");
	for(i=0;i<=g.vexnum-1;i++)
		printf("%4c",g.vexs[i]);
	printf("\n");
	for(i=0;i<=g.vexnum-1;i++)
	{
		printf("  %c  ",g.vexs[i]);
		for(j=0;j<=g.vexnum-1;j++)
		{
			if(g.kind==1||g.kind==2)
				printf("%d   ",g.arcs[i][j]);
			else
			{
				if(g.arcs[i][j]==INF)
					printf("�� ");
				else
					printf("%d  ",g.arcs[i][j]);
			}
		}
		printf("\n");
	}
}
struct arcnode
{
	int adjvex,weight;
	struct arcnode*nextarc;
};
struct vexnode
{
	char vexdata;
	struct arcnode*firstarc;
};
struct MGraph_Adj
{
	int vexnum,arcnum;
	struct vexnode vexarr[VEXNUM];
	int kind;
};
void create_Adj(struct MGraph_Adj *g)      //����ȫ��ͨ��ͼ�ζ���graph,����ͼ���ڽӱ�
{
	int i;
	struct arcnode *p=NULL;
	g->vexnum=graph.vexnum;
	g->arcnum=graph.arcnum;
	g->kind=graph.kind;
	for(i=0;i<=g->vexnum-1;i++)
	{
		g->vexarr[i].vexdata=graph.vexs[i];
		g->vexarr[i].firstarc=NULL;
	}
	for(i=0;i<=g->arcnum-1;i++)
	{
		p=(struct arcnode*)(malloc(sizeof(struct arcnode)));
		p->adjvex=graph.arcs[i*3+1];
		p->weight=graph.arcs[i*3+2];
		p->nextarc=g->vexarr[graph.arcs[i*3]].firstarc;
		g->vexarr[graph.arcs[i*3]].firstarc=p;
		if(g->kind==1||g->kind==3)
		{
			p=(struct arcnode*)(malloc(sizeof(struct arcnode)));
            p->adjvex=graph.arcs[i*3];
			p->weight=graph.arcs[i*3+2];
			p->nextarc=g->vexarr[graph.arcs[i*3+1]].firstarc;
			g->vexarr[graph.arcs[i*3+1]].firstarc=p;
		}
	}
}
void print_Adj(struct MGraph_Adj g)
{
	int i;
	struct arcnode *p=NULL;
	printf("\n\n");
	for(i=0;i<=g.vexnum-1;i++)
	{
		printf(" %d %c",i,g.vexarr[i].vexdata);
		p=g.vexarr[i].firstarc;
		while(p)
		{
			if(g.kind==1||g.kind==2)
				printf("->%d",p->adjvex);
			else
				printf("->%d|%d",p->adjvex,p->weight);
			p=p->nextarc;       //��һ�߱�
		}
		printf("\n");
	}
}
// ----------------------���Ƿָ���-------------------------


void Floyd_Mat(struct MGraph_Mat g)
{
	int i,j,k,m=1;
	int d[VEXNUM][VEXNUM];//�������
	int p[VEXNUM][VEXNUM];//���������
	
	for(i=0;i<=g.vexnum-1;i++)//��ʼ��floyd�㷨��d,p��������
		for(j=0;j<=g.vexnum-1;j++)
		{
			d[i][j]=g.arcs[i][j];//��������ʼ��-��������������
			p[i][j]=j;//����������ʼ��-Ĭ�϶���ֱ��i-j,��j
		}
		//��ʾ���������㷨�������-��ʾ��ʼ�������;��������
		printf("�������´������:\n %d.��ʼ�������(ֱ��)&���������(ֱ��)\n     ",m++);
		for(i=0;i<=g.vexnum-1;i++)
			printf("%3c ",g.vexs[i]);//��ʾ��һ�У����ڵ��ַ�
		printf("         ");
		for(i=0;i<=g.vexnum-1;i++)
			printf("%3c ",g.vexs[i]);//��ʾ��һ�У����ڵ��ַ�
		printf("\n") ;
		
		for(i=0;i<=g.vexnum-1;i++)//����
		{
			printf("  %c  ",g.vexs[i]);//����ʾ�ַ�
			for(j=0;j<=g.vexnum-1;j++)//����
				if(d[i][j]==INF)
					printf("%3s ", "��");//��ʾ����
				else
					printf("%3d ",d[i][j]);//�� ��ʾȨֵ
				printf("       %c ",g.vexs[i]);//����ʾ�ַ�
				for(j=0;j<=g.vexnum-1;j++)//����
					printf("%3d ",p[i][j]);//����ʾȨֵ
				printf("\n") ;
		}
		//
		for(k=0;k<=g.vexnum-1;k++)//kΪ����̽�⾭�����м��
		{
			for(i=0; i<=g.vexnum-1;i++)//iΪ���
				for(j=0;j<=g.vexnum-1;j++)//jΪ�յ�
					if((d[i][k]+d[k][j])<d[i][j]&&(i!=j))//�������k��С��i-j���о���
					{
						d[i][j]=d[i][k]+d[k][j];//������С����
						p[i][j]=p[i][k];//������С·���м��
					}
		
//��ʾ���������㷨�������-��ʾ����̽���ľ������;��������
					printf("\n %d.����̽��%d��ľ������&���������\n   ",m++,k);
					for(i=0;i<=g.vexnum-1;i++)
						printf("%3c ",g.vexs[i]);//��ʾ��һ�У����ڵ��ַ�
					printf("         ");
					for(i=0;i<=g.vexnum-1;i++)
						printf("%3c ",g.vexs[i]);//��ʾ��һ�У����ڵ��ַ�
					printf("\n");
					for(i=0;i<=g.vexnum-1;i++)//����
					{
						printf(" %c ",g.vexs[i]);//����ʾ�ַ�
						for(j=0;j<=g.vexnum-1;j++)//����
							if(d[i][j]==INF)
								printf("%3s ","��");//��ʾ����
							else
								printf("%3d ",d[i][j]);//����ʾȨֵ
							
						printf("       %c ",g.vexs[i]);//����ʾ�ַ�
						for(j=0;j<=g.vexnum-1;j++)//����
							printf("%3d ",p[i][j]);//����ʾȨֵ
						printf("\n");
					}
					//
		}
					printf("\n����֮������·��:\n");
					printf(" \t");
					for(i=0;i<=g.vexnum-1;i++)
						printf("%c\t",g.vexs[i]);
					printf("\n");
					for(i=0;i<=g.vexnum-1;i++)
					{
						printf(" %c\t",g.vexs[i]);
						for(j=0;j<=g.vexnum-1;j++)
							if(d[i][j]==INF)
								printf("��\t");
							else
							{
								printf("%d",d[i][j]);//��ʾ��õ���̾���
								k=p[i][j];
								if(k!=j)//����о�����
								{
									printf("-");
									while(k!=j)
									{//����ʾ������
										printf("%c",g.vexs[k]);//��ӡ�м��
										k=p[k][j];
									}
								}
								printf("\t");
							}
							printf("\n");
					}
}
/////////////////////////////////////////
void Floyd_Adj(struct MGraph_Adj g)

{
	int i,j,k;
	int p[VEXNUM][VEXNUM],d[VEXNUM][VEXNUM];
	struct arcnode *q=NULL;
	for(i=0;i<g.vexnum;i++)//��ʼ��floyd�㷨��d,p��������

		for(j=0;j<=g.vexnum;j++)////////////////////////////////////
		{
			d[i][j]=INF;
			p[i][j]=j;//���������
		}
		for(i=0;i<=g.vexnum-1;i++)//ѭ������������
		{
			q=g.vexarr[i].firstarc;
			while(q)//ѭ���߱�����
			{
				d[i][q->adjvex]=q->weight;//�������
				q=q->nextarc;
			}
		}
		for (k=0;k<g.vexnum;k++)//kΪ����̽�⾭�����м��
		{
			for(i=0;i<g.vexnum;i++)//iΪ���
				for(j=0;j<g.vexnum;j++)//jΪ�յ�
					if(d[i][j]>(d[i][k]+d[k][j])&&(i!=j))
					{
						d[i][j]=d[i][k]+d[k][j];//������С·��
						p[i][j]=p[i][k];//������С·���м䶥��
					}
		}
		printf("\n����֮������·��:\n");
		printf(" \t");
		for(i=0;i<=g.vexnum-1;i++)
			printf("%c\t",g.vexarr[i].vexdata);
		printf("\n");
		for(i=0;i<g.vexnum;i++)
		{
			printf(" %c\t", g.vexarr[i].vexdata);
			for(j=0;j<g.vexnum;j++)
				if(d[i][j]==INF)
					printf("��\t");
				else
				{
					printf("%d",d[i][j]);
					k=p[i][j];
					if(k!=j)
					{
						printf("-") ;
						while(k!=j)
						{
							printf("%c",g.vexarr[k].vexdata);//��ӡ�м��
							k=p[k][j];
						}
					}
						printf("\t");
				}
				printf("\n");
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
	struct MGraph_Mat g;
	struct MGraph_Adj g1;
	create_Mat(&g);
	Floyd_Mat (g);
	create_Adj(&g1);
	Floyd_Adj(g1);
	printf("\n");
	funp("����B203�ķ����������㷨�����ڽӾ����ڽӱ�ĳ���ʵ��");
}






