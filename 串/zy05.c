#include "stdio.h"
#include "stdlib.h"
#include "string.h"
struct str {
	char word[20];//�������19���ַ�
	int num;//���ʳ��ֵĴ���
	struct str *next;
};//��������ڵ�����
struct str *init() {
	struct str *hd=(struct str *)malloc(sizeof(struct str));
	hd->next=NULL;
	return hd;
}
void SF(struct str *hd) {
	struct str *p=hd->next;
	while(p!=NULL) {
		hd->next=p->next;
		free(p);
		p=hd->next;
	}
	free(hd);
}
void print (struct str *hd) {
	struct str *p=hd->next;
	int i=0;
	while(p!=NULL) {
		printf ("%s:%d\n",p->word,p->num);
		p=p->next;
		i++;
		if(i>=20)
			break;
	}
}
void savetofile(struct str *hd) {
	struct str *p=hd->next;
	FILE *fp=fopen ("D:\\2.txt","w" );
	while(p!=NULL) {
		fprintf(fp,"%s:%d\n",p->word,p->num);
		p=p->next;
	}
	fclose(fp);
}
void px (struct str *hd) {
	struct str *p=hd->next->next,*r,*t;
	hd->next->next=NULL;
	while(p!=NULL) {
		r=p;
		p=p->next;
		t=hd;
		while(t->next!=NULL&&t->next->num>r->num)
			t=t->next;
		r->next=t->next;
		t->next=r;
	}
}
void find (struct str *hd, char s[]) {
	struct str *p=hd->next;
	while(p!=NULL) {
		if(strcmp(p->word,s)==0)
			break; //����ҵ�����
		p=p->next;
	}
	if(p==NULL) { //û�ҵ����ʣ���Ϊһ���½���������
		struct str *p=(struct str *)malloc(sizeof(struct str));
		strcpy(p->word,s);
		p->num=1;
		p->next=hd->next;
		hd->next=p;
	} else //�ҵ��˸�����1
		p->num++;

}
void sclb(struct str *hd) {
	FILE*fp=fopen("D:\\1.txt ","r");
	int i=0,bz=0,k;
	char c,substr[20];//���������ַ����10000�����������19���ַ�
	while(!feof(fp)) {
		c=fgetc(fp);
		if(c>='A'&&c<='Z')
			c=c+32;
		if(c>='a'&&c<='z') { //�������ĸ
			if(bz==0) { //��bz=0��ʾ�µ��ʿ�ʼ
				k=0;
				substr[k++]=c;
				bz=1;//��ǵ��ʿ�ʼ
			} else //���µ��ʿ�ʼ����ԭ���ʺ�����ַ�
				substr[k++]=c;
		} else { //����Ƿ���ĸ�ַ������ʽ���
			if(bz==1) { //�������ĵ�һ���ո񣬱�ǵ��ʽ���
				bz=0;//һ�����ʽ������µ��ʿ�ʼ��־����������Ӣ����ĸ|�ַ����������µĵ���
				substr[k]='\0';//�ֶ������ɵ��Ӵ���������־
				find (hd,substr) ;
			}//�����������ĵ�2,3,4....�����ʣ�ʲôҲ����
		}
	}
	if(bz==1) {
		substr[k]='\0';//�������ĵ���
		find(hd,substr);
	}
	fclose(fp);
}
void main() {
	struct str *head=init();
	sclb(head) ;
	px(head);
	print(head) ;
	savetofile(head);
	SF(head);
}










