#include<stdio.h>//������߳ɹ������鼮�������á�ReaderUser�ṹ�塱
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#define maxsize 10
int AdminKey=0;//������Ա�Ƿ��½�ɹ���Ϊ1���½�ɹ�
int UserKey=0;//�������Ƿ��½�ɹ���Ϊ1���½�ɹ�
char bookname1[10];
int MaxSize=0;//������������
typedef struct bookinformation//ͼ����Ϣ,ֻ�й���Ա�ܷ���
{
	char bookname[maxsize];//����
	int bookstate;//���״̬ 0�������ģ�1��û������;
	int timelimit;//����ͼ�鱻���ģ�������ʱ������,ʱ������Ĭ��Ϊ30��;
	bookinformation *next;//nextָ��
}bookinformation;
//�����˻��ļ��ṹ��
//�˺� ����

typedef struct ReaderUser//��������
{
	char UserName[10];
	int BookSore;
	int Maxsize;
	ReaderUser *next;
}ReaderUser;

ReaderUser *RdUserHd;//���ƶ����˻��ĵ�����(��Ҫ��)
bookinformation *hd;//���������ĵ�����(��Ҫ��)
ReaderUser *p=(ReaderUser *)malloc(sizeof(ReaderUser));


void Actorfun(char s[])//�����Ȩ��Ϣ
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}
void Timefun()//��������
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("����ʱ��Ϊ%s\n��������Ϊ30��\n----------------------------------------------\n",asctime(timeinfo));
}
void CreateMyAccount()//�����˻�	��success��
{	char StuUsername[10];
	char StuPassword[10];
	char code[10];//��Կ
	char compare[10];//�Ƚ��ַ������м��̣�
	FILE *fpcode;//����Կ�ļ�
	int flag,keyfile;//keyfile:�û�ѡ��Ҫ��������Ա�˻����Ƕ����˻�
	printf("��ѡ����Ҫ������Ϊ����Ա�˻����Ƕ����˻�:\n����1����������Ա�˻�\n����2�����������˻�\n");scanf("%d",&keyfile);
	//�ļ����������˺ţ�����д�뵽�ļ�	: Account.txt		��
	FILE *fp;
	if(keyfile==1)//x=1ʱ����������Ա�˻�
	{
		printf("��������Ա�˻���Ҫ�ܳף�����������ܳף�\n");
		scanf("%s",&code);
		fpcode=fopen("code.txt","r");
		if(fpcode==NULL)
		{
			printf("��Կ�ļ������ڣ�\n");flag=0;fclose(fpcode);
		}
				fscanf(fpcode,"%s",&compare);
		if(strcmp(compare,code)==0)
		{
			printf("��Կ��ȷ����ӭע�����Ա\n");
			flag=1;
		}
		else 
		{
			printf("��Կ�������\n");
				flag=0;
		}
		if(flag==1)
		{
			printf("����������˺�(����)\n");scanf("%s",&StuUsername);printf("����������˻�����(��ĸ������)\n");scanf("%s",&StuPassword);
			fp=fopen("AdminAccount.txt","r+w");//�ļ���ʽ�� �û���   �û�����
			if(fp==NULL){printf("Error�� File is no found!\n");fclose(fp);exit(0);}
			fseek(fp,0,SEEK_END);
			fprintf(fp,"%d %s",StuUsername,StuPassword);fprintf(fp,"\n");
			printf("���Ĺ���Ա�˻��Ѵ�����ϣ�\n");
				fclose(fp);
		}
	}
	else
		if(keyfile==2)
	{
			printf("����������˺�(����)\n");scanf("%s",&StuUsername);printf("����������˻�����(��ĸ������)\n");scanf("%s",&StuPassword);
		fp=fopen("UserAccount.txt","r+w");//�ļ���ʽ�� �û���   �û�����
		if(fp==NULL){printf("Error��UserAccount.txt File is no found!\n");exit(0);}
		fseek(fp,0,SEEK_END);
		fprintf(fp,"%d %s 0",StuUsername,StuPassword);fprintf(fp,"\n");
		printf("���Ķ����˻��Ѵ�����ϣ�\n----------------------------------------------\n");
			fclose(fp);
	}
		else
			printf("����������ֲ��ԣ�\n----------------------------------------------\n");return ;

}

void DisplayAlltheUser()//��ʾ���ж���	(success)
{	char Username[10];
	char Password[10];
	FILE *fp;
	fp=fopen("UserAccount.txt","r");
	if(fp==NULL){printf("UserAccount is no found!\n");fclose(fp);exit(0);}
	printf("�˻�Ϊ:   ����Ϊ��\n");
			fscanf(fp,"%s %s",&Username,&Password);fprintf(fp,"\n");
	while(!feof(fp))
	{	
		printf("%s   %s\n",Username,Password);
		fscanf(fp,"%s %s",&Username,&Password);
	}
	printf("�����˻��Ѿ�ȫ�������ϣ�\n----------------------------------------------\n");
}
void BookInformationDisplay()//���ȫ��ͼ����Ϣ		(succss)
{
	char bookname1[maxsize];//����
	int bookstate1;//���״̬
	int timelimit1;//��Ľ������
	FILE *fp;
	fp=fopen("BookInformation.txt","r");
	if(fp==NULL){printf(" BookInformation.txt is no found!\n");fclose(fp);exit(0);}

	/*
	char bookname[maxsize];//����
	int bookstate;//���״̬ 0�������ģ�1��û������;
	int timelimit;//����ͼ�鱻���ģ�������ʱ������,ʱ������Ĭ��Ϊ30��;
	*/
	//�ļ���ʽ�� 
	printf("����  ���״̬(1�ɽ�/0���ɽ�) ���ʱ�����(��):\n");
	fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
	while(!feof(fp))
	{
		if(feof(fp))break;
	
		printf("%s   %d\t\t\t %d\n",bookname1,bookstate1,timelimit1);
		fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
	}
	printf("ͼ����Ϣȫ�������ϣ�\n----------------------------------------------\n");

}
void display()//��ʾ������ͼ����Ϣ�����������״̬���������		�������������
{	
	bookinformation *p;p=hd->next;//�����һ���ڵ�
	printf("----------------------------------------------\n");
	while(p)//�������
	{	
		printf("%s %d %d\n",p->bookname,p->bookstate,p->timelimit);
		p=p->next;
	}
	printf("\n----------------------------------------------\n");
}

bookinformation* search(bookinformation *hd1,int sum)//����ͼ��		(success)
{
	int i=1;
	bookinformation *p;
	p=hd1->next ;//�����һ���ڵ�
	if(sum==0)return hd;//������Ϊ0����ʾ�ö���û�н���      
	while(p&&i<sum)//û�ҵ���һֱ������
	{	p=p->next;
		++i;
	}
	return p;

}
void BookInformationInit()//					ͼ����Ϣ��ʼ������	
{
	bookinformation *p;	
	bookinformation *hd1;	hd1=(bookinformation *)malloc(sizeof(bookinformation));
	hd1=hd;
	printf("���ڳ�ʼ���������\n");
	char bookname1[maxsize];//����
	int bookstate1;//���״̬
	int timelimit1;//���ʱ�����
	FILE *fp;
	fp=fopen("BookInformation.txt","r+w");
	if(fp==NULL){printf("BookInformation.txt is no found!\n");fclose(fp);exit(0);}
	fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);//fscanf(fp,"\n");
	int sum=0;//����ͼ������
	while(!feof(fp))
	{		
		sum++;
		p=(bookinformation *)malloc(sizeof(bookinformation));
		strcpy(p->bookname,bookname1);//�ַ�����ֵ
		p->bookstate=bookstate1;//״̬��ֵ
		p->timelimit=timelimit1;//ʱ�丳ֵ
		
		hd1->next=p;//β�巨,���뵽������
		hd1=p;//β�巨
			fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
	}

	hd1->next=NULL;//β�巨
	printf("\nĿǰͼ�鹲��%d��\n\n",sum);
	printf("�����ʼ�����!\n----------------------------------------------\n");
	display();
	fclose(fp);
}
void BookInformationInput()//ͼ����Ϣ����	(success)
{	char Input[maxsize];//��Ϣ¼��
	FILE *fp;
	fp=fopen("BookInformation.txt","r+w");
	if(fp==NULL){printf("BookInformation.txt is no found!\n");fclose(fp);exit(0);}
	printf("�벻�������������(�����ֳ�����һ�£�)��ֱ������null\n");
	while(1)
	{	scanf("%s",&Input);
		if(strcmp(Input,"null")==0)
		{fclose(fp);	break;}
		fseek(fp,0,SEEK_END);//д�뵽�ļ�ĩβ
		fprintf(fp,"%s 1 00",Input);fprintf(fp,"\n");
		printf("�ɹ�¼���ͼ��\n");
	}
	BookInformationInit();
}



void BookInformationDelete()//ͼ����Ϣɾ��			(success!)
{	int sum=0,flag=0;//������,��־λ
	char bookname1[maxsize];
	bookinformation *q;
	printf("����������Ҫɾ����ͼ��������\n");
	scanf("%s",&bookname1);
	bookinformation *p,*w,*L;
	p=(bookinformation *)malloc(sizeof(bookinformation));
	L=(bookinformation *)malloc(sizeof(bookinformation));
	p=hd->next;//�����һ���ڵ�

//	printf("��һ����%s\n",p->bookname);
	while(p)//���������
	{	
		sum=sum+1;
			if(strcmp(p->bookname,bookname1)==0)//�����ȣ���ɾ����!
		{
			w=search(hd,sum-1);
			q=w->next;printf("Ҫɾ������%s�鼮\n",q->bookname);
			w->next=q->next;//ɾ���㷨
			free(q);//��qɾ��
			flag=1;
			printf("haven delete!\n");sum--;
			display();
			break;
		}
			p=p->next;
			
	}
	L=hd->next;
	if(flag==0)printf("\n----------------------------------------------\nҪɾ�����鼮δ�ҵ���\n----------------------------------------------\n");
	FILE *fp;
	fp=fopen("BookInformation.txt","w");
	if(fp==NULL){printf("BookInformation.txtδ�ҵ���\n");fclose(fp);exit(0);}
//	fseek(fp,0,SEEK_SET);
	while(L)
	{
		fprintf(fp,"%s %d %d",L->bookname,L->bookstate,L->timelimit);fprintf(fp,"\n");
		L=L->next;
	}
	fclose(fp);
	printf("ͼ�����ݿ��Ѹ���!\n----------------------------------------------\n");
//	BookInformationInit();
	
}

void AdminKeyControl()//����Ա�������
{	int x;//������Ӧ�Ĺ��ܣ�
	printf("����Ա������壺\n��������Ӧ�����ֽ�����Ӧ�Ĺ��ܣ�\n\n");

	printf("����1����ʾ�����ж����˻�������\n");
	printf("����2����ʾ����ͼ����Ϣ\n");
	printf("����3��ͼ����Ϣ¼��\n");
	printf("����4��ɾ��ͼ����Ϣ\n");
	printf("����5���˳��˺�\n");

	//printf("����1��\n");
	scanf("%d",&x);printf("----------------------------------------------\n");
	switch(x)
	{
		case 1:DisplayAlltheUser();break;//��ʾ�����ж����˻�������	
		case 2:BookInformationDisplay();break;//��ʾ����ͼ����Ϣ
		case 3:BookInformationInput();break;//ͼ����Ϣ¼��		
		case 4:BookInformationDelete();break;//ɾ��ͼ����Ϣ
		case 5:AdminKey=0;break;//�˳��˺�
	}
}
void AdminSearch(char username[],char password[])//�����˺ź������ѯ����Ա�������ڣ����½		//(success)
{	char username1[10];char password1[10];
	int outcome;
	FILE *fp;int flag=0;
	fp=fopen("AdminAccount.txt","r");//�ļ���ʽ���û���		�û�����
	if(fp==NULL){printf("AdminAccount.txtδ�ҵ���\n");fclose(fp);exit(0);}
	printf("----------------------------------------------\n");
	while(!feof(fp))
	{
		fscanf(fp,"%s %s",&username1,&password1);
		outcome=strcmp(password,password1);//�ַ����ȽϺ�������outcome=0ʱ�����������ַ������
		if(strcmp(username,username1)==0&&outcome==0)
		{
			printf("��ӭ��½��\n");
			flag=1;AdminKey=1;
			break;
		}
	}
	if(flag==0)
		printf("���˺Ų�����,�����µ�½��\n");
	while(AdminKey)
		AdminKeyControl();
}
void BookInformationSearch()//ͼ����Ϣ����	(success)
{
	char bookname1[maxsize];
	int bookstate1;
	int timelimit1;
	int flag=0,sore=0;//��־λ����ı��
	char search[maxsize];
	FILE *fp;
	fp=fopen("BookInformation.txt","r");
	if(fp==NULL){printf("BookInformation.txt is no found!\n");fclose(fp);exit(0);}
	printf("����������Ҫ��ѯ��ͼ��\n");scanf("%s",&search);printf("��ѯ���:\n");
	fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);fprintf(fp,"\n");
	while(!feof(fp))
	{	sore++;
		if(strcmp(bookname1,search)==0)
		{	flag=1;
			printf("\n������Ϣ���£�\n������%s\t�Ƿ�ɽ�(1�ɽ�/0���ɽ�):%d\n",bookname1,bookstate1);
			break;
			
		}
		fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
	}
	
		if(flag==0)printf("��ͼ�鲻���ڣ�\n");
	else
		printf("��ı�ţ�%d\n",sore);
	printf("----------------------------------------------\n");
}
void ReaderDatabaseInput(char string[])//�û����ݿ�д�� (BUG,�޷�д��)
{
	FILE *fp;
	char filename[10];

	strcpy(filename,string);
	strcat(filename,".txt");//�û���.txt
	fp=fopen(filename,"r+w");	//(bug!)


	if(fp==NULL){printf("ReaderDatabaseInput  %sδ�ҵ���\n",filename);fclose(fp);exit(0);}
	fseek(fp,0,SEEK_END);
	fprintf(fp,"%d\n",p->BookSore);//���鼮�ı��д���á������˻���������.txt�ļ���
	

//	fprintf(fp,"\n");
	printf("\n\nд����ϣ�����\n\n");
	fclose(fp);

}
char* BookSearch(int sore)//��ŵ���,���ñ�Ų���ͼ�����Ʋ�����
{		
	FILE *fp;
	static	char bookname1[10];
	int bookstate1,timelimit1,sore1=0;//���״̬�����ʱ������,��ı��
	fp=fopen("BookInformation.txt","r+w");

	if(fp==NULL){printf("BookSearch	��BookInformation.txtδ�ҵ���\n");fclose(fp);exit(0);}
	if(sore!=0)
	{
		fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);fprintf(fp,"\n");sore1++;
			while(!feof(fp)&&sore1<sore)
		{	sore1++;
			fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
			fprintf(fp,"\n");
			
		}
		fclose(fp);
	return bookname1;//�����ַ���
	}

	fclose(fp);
//	strcpy(bookname1,"");
//	return NULL;
	return bookname1;
}
void BookReturn()//�����㷨
{
	FILE *fp,*fp1;
	char BookName[10],filename[10];
	int Booksore1,Booksore,flag=0;
	char bookname1[maxsize];//����
	int bookstate1;//���״̬
	int timelimit1;//���ʱ�����
	printf("����������Ҫ�黹��ͼ���ţ�\n");
	scanf("%d",&Booksore);
	strcpy(BookName,BookSearch(Booksore));//����ͼ���ŷ���ͼ�����ƣ�����ֵ��BookName

	strcpy(filename,p->UserName);
	strcat(filename,".txt");
	fp=fopen(filename,"r+w");//fpָ�����	�û���.txt
	fp1=fopen("BookInformation.txt","r+w");//fp1ָ����� BookInformation.txt

	if(fp1==NULL){printf("�����㷨1��BookInformation.txt is no found!\n");fclose(fp1);exit(0);}
	if(fp==NULL){printf("�����㷨2��%s is no found!\n",filename);fclose(fp);exit(0);}

	fscanf(fp,"%d",&Booksore1);
	while(!feof(fp))//��ѯ�㷨
	{	
		if(Booksore1==Booksore)//�����Ҫ�黹��ͼ���ź����ѽ��ĵ��鼮�ı��һ��ʱ
		{
			printf("���Ϊ%d ����Ϊ  %s�Ѿ��ɹ��黹!\n",Booksore1,BookName);
			flag=1;
			break;//��ѯ��ϣ���ʼ�˳���ѯ�㷨
		}
		fscanf(fp,"%d",&Booksore1);
	}
	if(flag==0)printf("�㲢û�н����Ȿ���Ϊ%d���鼮��\n",Booksore);
	else
	{	
		for(int i=0;i<Booksore;i++)//��BookInformation.txt�ļ��н����������ΪBooksore�� λ��
			fscanf(fp1,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
				
			fseek(fp1,-4,SEEK_CUR);//�ɹ��黹�󣬿�ʼ��BookInformation.txt�ļ����лָ��͸��ģ�
			fprintf(fp1," 1 00");//(BUG!!!!)
			printf("ͼ����Ϣ���Ѿ�������ϣ���BookReturn��\n");

/*				fseek(fp,-4,SEEK_CUR);//x=30;				
	fprintf(fp," 0 30");								
*/

			fseek(fp,-1,SEEK_CUR);	//���� �û�.txt�ļ�����ɾ���� ���黹��ͼ����
			fprintf(fp,"0");
	}
						
					

	fclose(fp);
	fclose(fp1);
	printf("----------------------------------------------\n");
}
void BookBorrow()//ͼ�����			(BUG!!!!!)
{	BookInformationSearch();//���ò���ͼ��ĺ���
	char bookname1[maxsize];//����
	int bookstate1;//���״̬
	int timelimit1;//���ʱ�����
	int sore;
	FILE *fp;
	fp=fopen("BookInformation.txt","r+w");
	if(fp==NULL){printf("BookInformation.txt is no found!\n");fclose(fp);exit(0);}
	printf("��������Ҫ�����鼮�ı�ţ�\n");scanf("%d",&sore);printf("----------------------------------------------\n");
		for(int x=0;x<sore;x++)	
			fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
		if(bookstate1==0)
		{
			printf("��ͼ�������ޣ�����ȫ��������ϣ��뻻������н��ģ�\n----------------------------------------------\n");
			return ;
		}
		else
			
			if(p->Maxsize>5)
			{	
				printf("���Ѵﵽ��������!\n");
				return ;
			}
					//������߳ɹ������鼮�������á�ReaderUser�ṹ�塱
					//���鼮�ı��д���á������˻���������.txt�ļ���
					//RdUserHd
	printf("���Ѿ��ɹ����ı��Ϊ%d,����Ϊ  %s��ͼ�飡��ͼ���״̬��Ϊ0\n",sore,bookname1);
	Timefun();
//

		p->Maxsize++;//������++�����Ϊ5
		p->BookSore=sore;//ͼ���ŵ���
		ReaderDatabaseInput(p->UserName);
		
	fseek(fp,-4,SEEK_CUR);//x=30;				
	fprintf(fp," 0 30");								

printf("״̬�Ѹ��ģ�\n----------------------------------------------\n");	
fclose(fp);

}
void CreateReaderBookDatabase(char string[])//�����û��Լ������ݿ⣡
{
	FILE *fp;
	char filename[10];
	
	strcpy(filename,string);
	strcat(filename,".txt");
	fp=fopen(filename,"w");
	printf("�����û����ݿ���ɣ�������������������м��أ�\n�ļ���ʽΪ���û���.txt\n----------------------------------------------\n");
	fclose(fp);
	Actorfun("ͼ�����ϵͳ��");
//	if(fp==NULL){printf("CreateReaderBookDatabase:%sδ�ҵ���\n",filename);fclose(fp);exit(0);}
	
}


void HaveBorrowBookDisplay(char string[])//��ʾ�����ѽ��ĵ�ͼ�飡
{
	int Booksore1;//�鼮���
	FILE *fp;
	char BookName[10];
	char filename[10];
/*
	strcpy(filename,string);
	strcat(filename,".txt");//�û���.txt
	fp=fopen(filename,"r+w");
*/
	strcpy(filename,string);
	strcat(filename,".txt");
	fp=fopen(filename,"r+w");

	if(fp==NULL){printf("HaveBorrowBookDisplay  %sδ�ҵ���\n",filename);fclose(fp);exit(0);}
	printf("���ѽ��ĵ��鼮�У�\n");
	fscanf(fp,"%d",&Booksore1);//fscanf(fp,"\n");
	//printf("%d\n\n",Booksore1);
	while(!feof(fp))
	{	
		strcpy(BookName,BookSearch(Booksore1));//�ַ�����ֵ��BookName;
		if(strcmp(BookName,"NULL")==0)
		{fscanf(fp,"%d",&Booksore1);continue;		}

		if(Booksore1!=0)
			printf("���Ϊ%d ����Ϊ  %s\n",Booksore1,BookName);
		fscanf(fp,"%d",&Booksore1);//fscanf(fp,"\n");
	
	}
	
		
	fclose(fp);
	printf("----------------------------------------------\n");
	return ;
}
void UserKeyControl()//���߷������
{
	int x;//������Ӧ�Ĺ��ܣ�
	printf("���߷�����壺\n��������Ӧ�����ֽ�����Ӧ�Ĺ��ܣ�\n\n");

	//printf("����1����ʾ�����ж����˻�������\n");
	printf("����1������ͼ��\n");
	printf("����2����ѯͼ��\n");	
	printf("����3����ʾ����ͼ����Ϣ\n");
	printf("����4����ʾ�����ѽ����鼮\n");
	printf("����5������\n");
	printf("����6���˳��˺�\n");
	//printf("����1��\n");
	scanf("%d",&x);printf("----------------------------------------------\n");
	switch(x)
	{
		case 1:BookBorrow();break;//ͼ�����
		case 2:BookInformationSearch();break;//ͼ����Ϣ����	
		case 3:BookInformationDisplay();break;//��ʾ����ͼ����Ϣ
		case 4:HaveBorrowBookDisplay(p->UserName);break;//��ʾ�����ѽ����鼮
		case 5:BookReturn();break;//����
		case 6:UserKey=0;break;//�˳��˺�
	}
}
/*
void ScanfMaxSize()
{
	FILE *fp;
	char filename[10];
	strcpy(filename,p->UserName);
	strcat(filename,".txt");
	fp=fopen(filename,"r+w");
		fscanf(fp,"%d",&Booksore1);//fscanf(fp,"\n");//printf("%d\n\n",Booksore1);
	while(!feof(fp))
	{	
		strcpy(BookName,BookSearch(Booksore1));//�ַ�����ֵ��BookName;
		if(Booksore1!=0)
			MaxSize++;
	}
}
*/
void UserSearch(char username[],char password[])//�����˺ź������ѯ���ߣ������ڣ����½	//(success)
{
	char username1[10];char password1[10];
	int outcome;
	FILE *fp,*fp1;int flag=0;
	fp=fopen("UserAccount.txt","r");//�ļ���ʽ���û���		�û�����
	if(fp==NULL){printf("AdminAccount.txtδ�ҵ���\n");fclose(fp);exit(0);}
	printf("----------------------------------------------\n");
	while(!feof(fp))
	{	fscanf(fp,"%s %s",&username1,&password1);
		outcome=strcmp(password,password1);//�ַ����ȽϺ�������outcome=0ʱ�����������ַ������
		if(strcmp(username,username1)==0&&outcome==0)
		{
			printf("��ӭ��½��\n");
			flag=1;UserKey=1;	strcpy(p->UserName,username1);
			char filename[10];
			strcpy(filename,p->UserName);
			strcat(filename,".txt");//�û���.txt
			//printf("���ȴ������û������ݿ⣡�ļ���ʽ�û���.txt\n");exit(0);
			fp1=fopen(filename,"r+w");
			if(fp1==NULL){CreateReaderBookDatabase(p->UserName);fclose(fp1);}
		//	ScanfMaxSize();
			fclose(fp1);
			break;
		}
	}
	if(flag==0)
		printf("���˺Ų�����,�����µ�½��\n");
		while(UserKey)
		UserKeyControl();
}
void Login()//��½����				(success)
{	int usernamecontrol;
	char username[10];
	char password[10];
	printf("��ѡ��������:\n����1:����Ա�˺ŵ�½\n����2:�����˺ŵ�½\n");
	scanf("%d",&usernamecontrol);//�û���ݿ��ƣ������û���������һ����˻�;
	switch(usernamecontrol)
{
case 1:printf("��������Ĺ���Ա�˺�(��Ϊ����):\n");scanf("%s",&username);printf("��������Ĺ���Ա����(��Ϊ����):\n");scanf("%s",&password);break;
case 2:printf("��������Ķ����˺�(��Ϊ����):\n");scanf("%s",&username);printf("��������Ķ�������(��Ϊ����):\n");scanf("%s",&password);break;
default:printf("������ѡ�����ݲ����ڣ�\n");break;
}
	if(usernamecontrol==1)
	AdminSearch(username,password);//�����Ƿ���ڸù���Ա�˺�
	else
	UserSearch(username,password);//�����Ƿ���ڸö����˺� 
}


int  main()
{	hd=(bookinformation *)malloc(sizeof(bookinformation));
	hd->next=NULL;//ͷ���
	RdUserHd=(ReaderUser *)malloc(sizeof(ReaderUser));
	RdUserHd->next=NULL;//ͷ���
	p->Maxsize=0;
	BookInformationInit();
//	CreateReaderBookDatabase();
	int x;
	while(1)//�˵�����
	{	printf("��ӭ����ͼ�����ϵͳ��\n����1,�����˻�\n");
		printf("����2,�û���ݵ�½\n����3,�˳�ϵͳ\n----------------------------------------------\n");	scanf("%d",&x);
		switch(x)
		{
		case 1:CreateMyAccount();break;//����1,�����˻�
		case 2:Login();break;	//����2,�û���ݵ�½
		case 3:printf("���Ѿ��ɹ��˳�ͼ�����ϵͳ��\n");Actorfun("ͼ�����ϵͳ");exit(0);break;//�˳�ϵͳ
		default:printf("�����ڵĹ��ܣ����������룡\n");break;
		}
	}

//	CreateMyAccount();
//	Login();
return 0;
}
