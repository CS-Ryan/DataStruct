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
} graph={6,8,4,"ABCDEF",{0,5,100,0,4,30,0,2,10,1,2,5,2,3,50,3,5,10,4,3,20,4,5,60}};
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


void Dijkstra_Mat (struct MGraph_Mat g, int index)//Dijkstra�����·������index��ʾ��ʼ��
{
	int i,j,k;
    int min_j1,min_xb;//��С���롢��С���±�
    int used[VEXNUM];//��ǵ��Ƿ�ѡ���-���������
    int distance[VEXNUM];//index��ʼ�㵽�������̾���
    char path[VEXNUM] [VEXNUM];//��¼index��ʼ�㵽��������·��-�����ĵ�-�±�����
    int num[VEXNUM];//index��ʼ�㵽��������·������-�������������path��ά����һ��ʹ��
    for(i=0;i<=g.vexnum-1;i++)//ѭ��-���������
    {
		used[i]=0;//��ʼ����δΪѡ��
        path[i][0]=g.vexs[index];//��ʼ����·����ʼ���ַ���Ϊ-index��Ӧ���ַ�
        num[i]=1;//��ʼ�����������Ϊ1 (��Ϊ��·����һ���Ϊ��ʼ�㣬path[i][0]-0���ù������ô�1��ʼ)
    }
	for(i=0;i<=g.vexnum-1;i++)//ѭ��-���������
	{
		distance[i]=g.arcs[index][i];
             //��ʼ��index��ʼ�㵽�������̾���Ϊ:index���������ֱ�Ӿ��룬�������index��
        if(distance[i]!=INF)//���index�㵽ĳ���б�
			path[i][num[i]++]=g.vexs[i];//��¼�����ĵ��ַ�
               //num[i]++:�±��ú�++����Ϊ����һ��ʹ����׼��
	}
//��ʾ����-ֱ��������
	printf("   �Ͻ�˹��������: ");
    printf("\n\t\t  ");
    for(i=0;i<=g.vexnum-1;i++)
    {
		if(i==index) continue;//����������
        printf("v%d\t",i);//��ʾ�����
	}
    printf(" ѡ����С ");
    printf("\n  v%dֱ��������: ",index);
    for(i=0;i<=g.vexnum-1;i++)//��ʾ��һ��ֱ��������
	{
		if(i==index) continue;
		if(distance[i]==INF)//���index��i�����̾���Ϊ����
			printf("��\t");
		else
			printf("%d\t",distance[i]);
	}
	//
	used[index]=1;//������ʼ��indexʹ�ù����
	for(i=0;i<=g.vexnum-2;i++)//��ѡ��������-���������1��
	{
		min_xb=index+1;//������ʼ����һ��Ϊ�����
        min_j1=INF;//��������ֵΪ����
        for(j=0;j<=g.vexnum-1;j++)//ѭ�������·����-ѭ�����������1��
		{
			if((used[j]==0)&&(distance[j]<min_j1))
            //���k��δѡ���Ҿ���С��min_ j1��
			{
				min_j1=distance[j];//��� ����
                min_xb=j;//��¼�ҵ���������±�
			}
		}
//ѭ��������min_ j1Ϊ�ҵ���������룬min_xbΪ�ҵ���������±�
//
		if(min_j1==INF)
            printf("�ҵ������v%d(��)\n",min_xb);
        else
            printf("�ҵ������v%d(%d)\n",min_xb,min_j1);
//
		used[min_xb]=1;//����ҵ��������-��ʹ�ù�
        for(j=0;j<=g.vexnum-1;j++)
//����жϾ������min_ xb�����ξ���֮�ͣ��Ƿ�С��ԭ���룬�������-ѭ�����������1��
		{
			if((used[j]==0)&&(distance[min_xb]+g.arcs[min_xb][j]<distance[j]))
//�������min_ _xb��·������
			{
				distance[j]=distance[min_xb]+g.arcs[min_xb][j];//���¾� ��
                for(k=0;k<=num[min_xb]-1;k++)
					path[j][k]=path[min_xb][k];//���¸���·��
				num[j]=num[min_xb];//���ƾ��������
				path[j][num[j]++]=g.vexs[j];
				//���·���㣬��num[k]++��1Ϊ��һ��ʹ����׼��
			}
		}
//��ʾ�������
		printf("����v%d����̾���: ",min_xb);
        for(j=0;j<=g.vexnum-1;j++)
		{
			if(j==index) continue;//ͬһ�����
			if(distance[j]==INF)//���index��i�����̾���Ϊ����
				printf(" ��\t");
			else
				printf("%d\t",distance[j]);
		}
	}
	//��ʾ���
	printf("\n\n  v%d����������·������Ϊ:\n", index);//index��Դ��ʼ���ַ�
	for(i=0;i<=g.vexnum-1;i++)//��ʼ�㵽����������±�
	{
		if(i==index) continue;
		
			printf("    %c-%c\t",g.vexs[index],g.vexs[i]);
			if(distance[i]==INF)//���index��i�����̾���Ϊ����
				printf("   ��\t");
			else
			{
				printf("   %d\t",distance[i]);//�� ʾindex��i�����̾���
			    printf("%c",path[i][0]);//��̾���-·��-��ʼ��
				for(j=1;j<=num[i]-1;j++)
					printf("-%c",path[i][j]);//��̾����·��-��������
			}
			printf("\n");
		}
}
void Dijkstra_Adj(struct MGraph_Adj g,int index)//Dijkstra�����·������index��ʾ��ʼ��
{
	int i,j;
	int min_xb,min_j1;//��С�±ꡢ��С����
	int used[VEXNUM];//��ǵ��Ƿ�ʹ�ù�
    int distance[VEXNUM];//���� ��ľ���
    char path[VEXNUM] [VEXNUM];//��¼��·�������ĵ�
    int num[VEXNUM];//exp���� �±�
    struct arcnode *p=NULL;
	for(i=0;i<=g.vexnum-1;i++)
	{
		used[i]=0;//��ʼ����δʹ�ù�
		path[i][0]=g.vexarr[index].vexdata;//���ø�·����ʼ��
		num[i]=1;
	}
	for(i=0;i<=g.vexnum-1;i++)
		distance[i]=INF;
	p=g.vexarr[index].firstarc;
	while(p)//ѭ���߱�����
	{
		distance[p->adjvex]=p->weight;//�б߸��¾���
		path[p->adjvex][num[p->adjvex]++]=g.vexarr[p->adjvex].vexdata;
		p=p->nextarc;
	}
//
	used[index]=1;//������ʼ��indexʹ�ù����
	for(i=0;i<=g.vexnum-2;i++)//��ѡ��������
	{
		min_xb=index+1;//������ʼ����һ��Ϊ�����
		min_j1=INF;//��������ֵΪINF
		for(j=0;j<=g.vexnum-1;j++)//ѭ�������·����

		{
			if((used[j]==0)&&(distance[j]<min_j1))
			{
				min_j1=distance[j];//����� ��
				min_xb=j;          //jΪ�ո��ҵ���V-U�� ��Դ��·����̵Ķ���
			}
		}
		used[min_xb]=1;//��������ʹ�ù����
		p=g.vexarr[min_xb].firstarc;
		while(p)//�������min_ xb���ı߱�����
		{
			if((used[p->adjvex]==0)&&(distance[min_xb]+p->weight<distance[p->adjvex]))//�������min. _xb��·������
			{
				distance[p->adjvex]=distance[min_xb]+p->weight;//���¾���
				for(j=0;j<num[min_xb];j++)
					path[p->adjvex][j]=path[min_xb][j];//���Ƹ���·��
				num[p->adjvex]=j;
				path[p->adjvex][num[p->adjvex]++]=g.vexarr[p->adjvex].vexdata;//���·����
			}
			p=p->nextarc;
		}
	}

	printf("\n %c����������·������Ϊ:\n",g.vexarr[index].vexdata);
	for(i=0;i<=g.vexnum-1;i++)
	{
		if(i==index) continue;
		printf("    %c-%c\t",g.vexarr[index].vexdata,g.vexarr[i].vexdata); 
		if(distance[i%g.vexnum]==INF)
			printf("  ��\t");
		else
		{
			printf("  %d\t",distance[i]);
			printf("%c",path[i][0]);//��̾���-·��-��ʼ��
			for(j=1;j<num[i];j++)
				printf("-%c",path[i][j]);
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
	Dijkstra_Mat(g,0);
	create_Adj(&g1);
	Dijkstra_Adj(g1,0);

	printf("\n");
	funp("�Ͻ�˹�����㷨�����ڽӾ����ڽӱ�ĳ���ʵ��");
}




