#include <stdio.h>
#include <stdlib.h>

typedef struct xs
{
	int data ;
	struct xs *prev ;
	struct xs *next ;
}DL ; 
void clear(DL *header)
{
	DL *p,*q;p=header;
	while(p->next==NULL)
	{
		q=p->next;
		free(p);
		p=q;
	}
	header->next=NULL;
	printf("˫��������ɾ��:\n");

}
DL *createnode(int data)
{
	DL *p = malloc(sizeof(DL));
	if(NULL == p)
	{
		printf("û�пռ���!\n");
		return NULL ;
	}

	p->data = data ;

	p->next = NULL ;
	p->prev = NULL ;
}
 

void tail_insert(DL *header , DL *new)
{

	DL *p = header ;

	while(NULL != p->next)
	{

		p = p->next ;
	}

	p->next = new ;

	new->prev = p;
}
 

void top_insert(DL *header , DL *new)
{

	new->next = header->next ; 

	if(NULL != header->next) 
		header->next->prev = new ; 
	header->next = new ;
	new->prev = header ;
}
 

void display1(DL *header)
{
	DL *p = header ;
	while(NULL != p->next)
	{
		p = p->next ;
		printf("%d ",p->data);
	}
}
 
void display2(DL *header)
{
	DL *p = header ;
	while(NULL != p->next)
	{
		p = p->next ;	
	} 
	while(NULL != p->prev)
	{
		printf("%d ",p->data);
		p = p->prev ;
	}
}
 
int delete_node(DL *header,int data)
{
	DL *p = header;
	while(NULL != p->next)
	{
		p = p->next ;
		if(p->data == data)
		{
			if(p->next != NULL)
			{ 
				p->next->prev = p->prev ;
				p->prev->next = p->next ;
				free(p);
			}
			else
			{
				p->prev->next = NULL ;
				free(p); 
			}
			return 0 ;
		}
	}
	printf("\nû���ҵ���ӦҪɾ���Ľڵ㣬���߽ڵ��Ѿ���ɾ����\n");
	return -1 ;	
} 
 
int main(void)
{
	int i ;
	DL *header = createnode(0);
	for(i = 0 ; i < 10 ; i++)
	{
		//˫�������β�� 
		//tail_insert(header,createnode(i));
		//˫�������ͷ�� 
		top_insert(header,createnode(i));
	}
	//˫�������������� 
	printf("˫��������������:");
	display1(header);putchar('\n');
	printf("���������ִ�У�\n");
	top_insert(header,createnode(233));display1(header);putchar('\n');
	printf("ɾ��������Ϊ5�Ľڵ�\n");
	delete_node(header,5);
	display1(header);
	putchar('\n');
	printf("˫������ķ������:");
	display2(header);putchar('\n');
	clear(header);display1(header);
	return 0 ;
}