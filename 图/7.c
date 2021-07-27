#include "stdio.h" 
#include "stdlib.h"
#include<time.h>
#define VEXNUM 9
#define ARCNUM 11
#define INF 9999    //�����
struct Graph        //ͨ��ͼ�ζ��壬���ڴ���ͼ�ε��ڽӾ�����ڽӱ�-ȫ�ֱ���
{
	int vexnum,arcnum,kind;//��������������ͼ���ͣ�1234-����ͼ������ͼ����������������
	char vexs[VEXNUM+1];   //�����ַ�����
	int arcs[ARCNUM*3];     //����ֹ���±꼰Ȩֵ����
} graph={9,11,4,"123456789",
{0,1,6,0,2,4,0,3,5,1,4,1,2,4,1,3,5,2,4,6,9,4,7,7,5,7,4,6,8,2,7,8,4}};
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

struct Activity
{
	int u;//����
    int v;//��յ�
    int w;//Ȩֵ
    int e;//����緢��ʱ��
    int l;//���ٷ���ʱ��
};        //�(��)--���ݴ洢����
void CritPath_Mat(struct MGraph_Mat g)//�����ڽӾ���洢�Ĺؼ�·���Ƶ�
{
	int i,j,k=0,min=INF;
    int ve[VEXNUM];                  //�¼�(����)�����緢��ʱ������
    int vl[VEXNUM];                  //�¼�(����)����ٷ���ʱ������
    struct Activity act[ARCNUM];     //�(��) ����

    for(i=0;i<=g.vexnum-1;i++)
	{
		ve[i]=0;                       //��ʼ���������¼����緢��ʱ��
        vl[i]=INF;                     //��ʼ���������¼���ٷ���ʱ��
	}
	for(i=0;i<=g. vexnum-1;i++)               //�����������
		for(j=0; j<=g. vexnum-1; j++)      //�����������
            if(g. arcs[i][j]!=INF)        //���������
			{
				act[k].u=i;                 //�(��)���
                act[k].v=j;                //�(��)�յ�
                act[k].w=g.arcs[i][j];     //�(��)Ȩֵ
                k++;
            }

	for(i=0;i<=g.arcnum-1;i++)                  //������������
        if(ve[act[i].u]+act[i].w>ve[act[i].v])   //��������¼������緢��ʱ��
                  //�� ���(��)������緢��ʱ��+�(��)Ȩֵ>�(��)���յ����緢��ʱ��
           ve[act[i].v]=ve[act[i].u]+act[i]. w;
                 //����»(��)�յ�����緢��ʱ�䣬���ж���·��ȡ���
     vl[g. vexnum-1]=ve[g. vexnum-1];
                 //����յ����ٷ���ʱ�䣬��ʼΪ����յ�����緢��ʱ��
     for(i=g.arcnum-1;i>=0;i--)                  //���յ���ǰ��������-�Ӻ���ǰ��
         if(vl[act[i].v]-act[i].w<vl[act[i].u])  //��������¼�����ٷ���ʱ��
                 //����(��)�� ����ٷ���ʱ��-�(��)Ȩֵ<�(��)�����ٷ���ʱ��
              vl[act[i].u]=vl[act[i].v]-act[i].w;
                     //����»(��)������ٷ���ʱ�䣬���ж���·��ȡС��
     printf("���¼������翪ʼʱ��/��ٿ�ʼʱ��:\n     ");
	 for(i=0; i<=g.vexnum-1; i++)
         printf(" v%c   ",g.vexs[i]);         //��ʾ�������ַ�
      printf("\n");
      printf("Ve[i]:");
      for(i=0; i<=g. vexnum-1;i++)
           printf("%-6d",ve[i]);//��ʾ���¼�(����)���緢��ʱ��
      printf("\n");
      printf("Vl[i]:");
	  for(i=0;i<=g.vexnum-1;i++)
      printf("%-6d",vl[i]);       //��ʾ���¼�(����)��ٷ���ʱ��
      for(i=0;i<=g.arcnum-1;i++)//��ǰ������
	  {
          act[i].e=ve[act[i].u];
             //���(��)���緢��ʱ�䣬���Ǹ����������緢��ʱ��
          act[i].l=vl[act[i].v]-act[i].w;
             //���(��)��ٷ� ��ʱ�䣬���Ǹ����յ����ٷ���ʱ��-��Ȩֵ
	  }
      printf("\n��������翪ʼʱ��/��ٿ�ʼʱ��: \n    ");

      for(i=0; i<=g.arcnum-1;i++)      //��ʾ���(��)
          printf("v%c-v%c ",g.vexs[act[i].u],g.vexs[act[i].v]);
      printf("\n");

      printf("e[i]:");
      for(i=0; i<=g. arcnum-1;i++) //��ʾ���(��)�����緢��ʱ��
           printf("%-6d" ,act[i].e);
      printf("\n") ;
      printf("l[i]:");
      for(i=0; i<=g.arcnum-1;i++) //��ʾ���(��)����ٷ���ʱ��
      printf("%-6d" ,act[i].l);

      printf("\n�ؼ�·��:\n");
      for(i=0;i<=g.arcnum-1;i++)
          if(act[i].e==act[i]. l)//���(��)��������ٷ���ʱ����ȣ����ǹؼ�·��-��ʾ
			  printf("v%c-v%c  ",g.vexs[act[i].u],g.vexs[act[i].v]);
      printf("\n");
}
//�������ڽӱ�
void CritPath_Adj(struct MGraph_Adj g)//�����ڽӱ�洢�Ĺؼ�·���Ƶ�
{
    int i,k=0;
    int ve[VEXNUM];//�¼�(����)�����緢��ʱ������
    int vl[VEXNUM];//�¼�(����)����ٷ���ʱ������
    struct Activity act[ARCNUM];//�� ��(��)����
    struct arcnode *p=NULL;

	for(i=0;i<=g.vexnum-1;i++)
	{
        ve[i]=0;//��ʼ���������¼����緢��ʱ��
        vl[i]=INF;//��ʼ���������¼���ٷ���ʱ��
	}
    for(i=0;i<=g. vexnum-1;i++)//ѭ������������
	{
        p=g.vexarr[i].firstarc;
        while(p)//ѭ���߱����㣬���������
		{
             act[k].u=i;//�(��)���
             act[k].v=p->adjvex;//�(��)�յ�
             act[k].w=p->weight;//�(��)Ȩֵ
			 k++;
			 p=p->nextarc;
		}
	}

	for(i=0; i<=g.vexnum-1; i++)//ѭ������������
	{
         p=g.vexarr[i].firstarc;
         while(p)//ѭ���߱�����
		 {
              if(p->weight+ve[i]>ve[p->adjvex])//��������¼������緢��ʱ��....
                                  //����(��)������緢��ʱ��+�(��)Ȩֵ>�(��)���յ����緢��ʱ��
                    ve[p->adjvex]=p->weight+ve[i];
                                 //����»(��)�յ�����緢��ʱ�䣬���ж���·��ȡ���
               p=p->nextarc;
		 }
	}

    vl[g.vexnum-1]=ve[g.vexnum-1];
            //����յ����ٷ���ʱ�䣬��ʼΪ����յ�����緢��ʱ��
    for(i=g.arcnum-1;i>=0;i--) //���յ���ǰ��������-�Ӻ���ǰ�Ƶ�
        if(vl[act[i].v]-act[i].w<vl[act[i].u])//��������¼�����ٷ���ʱ��
                 //����(��)�յ���ٷ���ʱ��-�(��)Ȩֵ<�(��)�����ٷ���ʱ��
             vl[act[i].u]=vl[act[i].v]-act[i].w;
		             //����»(��)������ٷ���ʱ��
     printf("\n���¼������翪ʼʱ��/��ٿ�ʼʱ��: \n");
     for(i=0;i<=g.vexnum-1;i++) //��ʾ�������ַ�
         printf("v%c    ",g.vexarr[i]);
     printf("\n");
     for(i=0;i<=g.vexnum-1; i++)
          printf("%-6d",ve[i]);//��ʾ���¼�(����)���緢��ʱ��
     printf("\n") ;
     for(i=0; i<=g.vexnum-1;i++)
          printf("%-6d",vl[i]);//��ʾ���¼�(����)��ٷ���ʱ��

	 for(i=0;i<=g.arcnum-1;i++) //��ǰ������
	 {
          act[i].e=ve[act[i].u];
           //���(��)���緢��ʱ�䣬���Ǹ����������緢��ʱ��
          act[i].l=vl[act[i].v]-act[i].w;
           //���(��)��ٷ���ʱ�䣬���Ǹ����յ����ٷ���ʱ��-��Ȩֵ
	 }
	 printf("\n��������翪ʼʱ��/��ٿ�ʼʱ��: \n");
     for(i=0;i<=g.arcnum-1;i++) //��ʾ���(��)
          printf("v%c-v%c ", g.vexarr[act[i].u].vexdata,g.vexarr[act[i].v].vexdata) ;
     printf("\n");
     for(i=0;i<=g.arcnum-1;i++) //��ʾ���(��)�����緢��ʱ��
         printf("%-6d",act[i].e);
     printf("\n");
     for(i=0;i<=g.arcnum-1;i++) //��ʾ���(��)����ٷ���ʱ��
         printf("%-6d",act[i].l);
     printf("\n�ؼ�·��:\n");
     for(i=0; i<=g.arcnum-1;i++)
          if(act[i].e==act[i].l)//���(��)��������ٷ���ʱ�����,���ǹؼ�·��-��ʾ
               printf("v%c-v%c  ",g.vexarr[act[i].u].vexdata,g.vexarr[act[i]. v]. vexdata);
     printf("\n");
}
//
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
	CritPath_Mat(g);
    create_Adj(&g1);
	CritPath_Adj(g1);

	printf("\n");
	funp("AOVͼ�ؼ�·���ڽӾ����ڽӱ�ĳ���ʵ��");
}










