#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 20
#define Q 40
//�������ݽṹ


struct CHENGKE//�����˿ͽṹ��
{
    
    
    char xingming[10];//����
    char zhengjianhao[20];//֤����
    int dingpiaoshu;//��Ʊ��
    char hangbanhao[10];//���������
    char bianhao[10];//���
};


struct HANGBAN//��������ṹ��
{
	char hangbanming[10];//������
    char qifeichengshi[20];//��ɳ���/
    char jiangluochengshi[20];//�������
    char qifeishijian[20];//���ʱ��
    char jiangluoshijian[20];//����ʱ��
    int zuoweishu;//��λ��
    char piaojia[5];//Ʊ��
    char zhekou[5];//�ۿ�
	CHENGKE chengke[20];
    int sit;
};
int menu_select()
{
int c;
printf("�밴������������˵�\n");//��ʾ�����������
getchar();//���������ַ�
printf("**********************************��ӭ����************************************\n");
printf("                            �Ϸ����շɻ���Ʊ����ϵͳ\n\n");
printf(" ***********************************���˵�*************************************\n\n");
printf("                           0.���뺽����Ϣ\n");
printf("                           1.�г��������Ϣ\n");
printf("                           2.������Ų�ѯ������Ϣ\n");
printf("                           3.����������ѯ����\n");
printf("                           4.��Ʊ\n");
printf("                           5.��Ʊ\n");
printf("                           6.�޸ķɻ��������Ϣ\n");
printf("                           7.�����ļ�\n");
printf("                           8.�˳�\n");
printf(" *************************��ӭ�´�ʹ�ã��ټ�*****************************************\n\n");
do
{
printf("\n ��������Ҫѡ��Ĺ���ѡ��(0~8):");
scanf("%d",&c);//����ѡ����
}
while(c<0||c>8);
return c;//����������ֲ��ڷ�Χ��
}





//���뺯��
int enter(HANGBAN t[])
{
int i,k,n,m,w,j;
char *s;
printf("���뺽������(n<=40):");//���뺽������
scanf("%d",&n);
while(n>40||n<0)
{
printf("You  put  is   wrong,please  put  again(0<n<=40):");
scanf("%d",&n);
}
printf("                 �����뺽�����Ϣ\n\n");
printf("������       ��ɳ���        �������        ����ʱ��        ����ʱ��        ʣ�µ���λ       �۸�       �ۿ�\n");
for(i=0;i<n;i++)
{
scanf("%s",t[i].hangbanming);
scanf("%s",t[i].qifeichengshi);
scanf("%s",t[i].jiangluochengshi);
scanf("%s",t[i].qifeishijian);
scanf("%s",t[i].jiangluoshijian);
scanf("%d",&t[i].zuoweishu);
scanf("%s",t[i].piaojia);
scanf("%s",t[i].zhekou);
}

printf("*****************************************************************************************\n");
for(i=0;i<n;i++)t[i].sit=0;
return n;//���ؼ�¼����
}








//��ʾ��¼������Ϊ��¼����ͼ�¼����
void list(HANGBAN t[],int n)
{
int i;
printf("������     ��ɳ���        �������         ����ʱ��        ����ʱ��     ʣ�µ���λ   �۸�    �ۿ�\n");
printf("*************************************************������Ϣ����**************************************************************\n");
for(i=0;i<n;i++)
printf("%-12s%-12s%-12s%-12s%-14s%-10d%-8s%-10s\n",t[i].hangbanming,t[i].qifeichengshi,t[i].jiangluochengshi,t[i].qifeishijian,t[i].jiangluoshijian,t[i].zuoweishu,t[i].piaojia,t[i].zhekou);
printf(" **************************************************end**********************************************************************\n");
}






//������Ų��Ҽ�¼
void search1(HANGBAN t[],int n)
{char s[20];//��������Һ������ַ���
int i;
printf("����������ҵĺ�����:");
scanf("%s",s);//��������Һ�����
for(i=0;i<n;i++)//�ӵ�һ����¼��ʼ�Ƚ�
{
if(strcmp(s,t[i].hangbanming)==0)//��¼�еĺ������ʹ��Ƚϵ��Ƿ����
break;//�ҵ�Ҫ�ҵĺ��࣬����
}
if(i>n-1)//û���ҵ���Ҫ�ҵĺ���
printf("---------------------------�ܱ�Ǹ��û���ҵ�����Ҫ���ҵĺ���-------------------------\n");
else
{
printf("������   ��ɳ���    �������      ����ʱ��        ����ʱ��     ʣ�µ���λ   �۸�     �ۿ�\n");//��ʾ��¼
printf("------------------------------------------------------------------------------\n");
printf("%-12s%-12s%-12s%-12s%-14s%-10d%-8s%-10s\n",t[i].hangbanming,t[i].qifeichengshi,t[i].jiangluochengshi,t[i].qifeishijian,t[i].jiangluoshijian,t[i].zuoweishu,t[i].piaojia,t[i].zhekou);
}
}



//���𽵳��в��Ҽ�¼
void search2(HANGBAN t[],int n)
{
char s1[20];
char s2[20];
int i;
printf("������ɳ�������:");
scanf("%s",s1);//������ɳ�����
printf("���뽵���������:");
scanf("%s",s2);//���뽵�������
for(i=0;i<n;i++)//�ӵ�һ����¼��ʼ�Ƚ�
{
if((strcmp(s1,t[i].qifeichengshi)==0)&&(strcmp(s2,t[i].jiangluochengshi)==0))//��¼�еĳ��кʹ��Ƚϵ��Ƿ����
break;//��ȣ��������
}
if(i>n-1)//û���ҵ���Ҫ�ҵĺ���
printf("-------------------------------------�ܱ�Ǹ��û���ҵ�����Ҫ���ҵĺ���---------------------------------------\n");
else
{
printf("������     ��ɳ���     �������     ����ʱ��       ����ʱ��     ʣ�µ���λ     �۸�     �ۿ�\n");//�ҵ�,��ʾ��¼
printf("------------------------------------------------------------------------------\n");
printf("%-12s%-12s%-12s%-12s%-14s%-10d%-8s%-10s\n",t[i].hangbanming,t[i].qifeichengshi,t[i].jiangluochengshi,t[i].qifeishijian,t[i].jiangluoshijian,t[i].zuoweishu,t[i].piaojia,t[i].zhekou);
}
}




//��Ʊ
void book(HANGBAN t[],int n)
{
char s[20],bianhao1[10],xingming1[10],zhengjianhao1[20],hangbanhao1[10];
int i,j=0,m,k,dingpiaoshu1;
printf("��������Ԥ����Ʊ��:");
scanf("%d",&m);
printf("--------------------------------------------------------------------------------------------------------------\n");
printf("���       ����       ֤����          ����Ʊ��             �����\n");//��ʾ��Ϣ
for(k=0;k<m;k++)
{
scanf("%s",bianhao1);
scanf("%s",xingming1);
scanf("%s",zhengjianhao1);
scanf("%d",&dingpiaoshu1);
scanf("%s",hangbanhao1);
for(i=0;i<n;i++)//�ӵ�һ����¼�Ƚϣ��Ƿ���Ҫ�ҵĺ���
{
if(strcmp(hangbanhao1,t[i].hangbanming)==0)//��¼�еĺ������ʹ��Ƚϵ��Ƿ����
{
j=t[i].sit;
strcpy(t[i].chengke[j].bianhao,bianhao1);
strcpy(t[i].chengke[j].xingming,xingming1);
strcpy(t[i].chengke[j].zhengjianhao,zhengjianhao1);
t[i].chengke[j].dingpiaoshu=dingpiaoshu1;
strcpy(t[i].chengke[j].hangbanhao,hangbanhao1);
t[i].zuoweishu=t[i].zuoweishu-dingpiaoshu1;
t[i].sit++;
break;//��ȣ��������
}
}
if(i>n-1)//û���ҵ���Ҫ�ҵĺ���
{
printf("-------------------------------------------�ܱ�Ǹ��û����Ҫ�ҵĺ���---------------------------------------\n");
m=m+2;
k++;
}
}
}



void save(HANGBAN t[],int lenght)//�����ļ�
{
	
	 const char* filename1 = "E:/X.txt";
    int dataindex =lenght;//�ļ��ĳ���
    FILE* fp1 = fopen(filename1 , "w");
	if (fp1 == NULL)//�ļ�����
	{
	    puts("Fail to open file!");//���ļ�ʧ��
	    exit(1);
	}
	for (int i = 0; i < dataindex; i++)
	{
	  fprintf(fp1, "%-12s%-12s%-12s%-12s%-14s%-10d%-8s%-10s\n",t[i].hangbanming,t[i].qifeichengshi,t[i].jiangluochengshi,t[i].qifeishijian,t[i].jiangluoshijian,t[i].zuoweishu,t[i].piaojia,t[i].zhekou);
	}//�������������
	fclose(fp1);
        printf("Data saved.\n");//�����ѱ���

}



//��Ʊ
void quit(HANGBAN t[],int n)
{
char s1[20],s2[20];//��������Һ�������֤�����ַ���
int i,k,j,h,l,ch;
printf("�����������˶��ĺ����:");
scanf("%s",s1);//��������Һ�����
printf("���������֤����:");
scanf("%s",s2);//���������֤����
printf("���     ����       ֤����        ����Ʊ��  �����\n");//��ʾ��ʾ
printf("------------------------------------------------------------\n");
for(i=0;i<n;i++)//�ӵ�һ����¼��ʼ��ֱ�����һ��
{
for(j=0;j<t[i].sit;j++)
if((strcmp(s1,t[i].chengke[j].hangbanhao)==0)&&(strcmp(s2,t[i].chengke[j].zhengjianhao)==0))
{
printf("%-11s%-16s%-16s%-14d%-10s\n",t[i].chengke[j].bianhao,t[i].chengke[j].xingming,t[i].chengke[j].zhengjianhao,t[i].chengke[j].dingpiaoshu,t[i].chengke[j].hangbanhao);
t[i].zuoweishu=t[i].zuoweishu+t[i].chengke[j].dingpiaoshu;
l=j;
h=i;
break;
}
}
i=h;
if(i>n-1)//�������iֵ����n-1,˵��û�ҵ�
printf("û���ҵ�\n");
else
{
printf("���Ƿ�ȷ��ɾ��(1/0)\n");//ȷ���Ƿ�Ҫɾ��
scanf("%d",&ch);//����һ��������
if(ch==1)//���ȷ��ɾ������Ϊ
{
for(k=l+1;k<t[i].sit;k++)
{
strcpy(t[i].chengke[k-1].bianhao,t[i].chengke[k].bianhao);//����һ����¼������������ǰһ��
strcpy(t[i].chengke[k-1].xingming,t[i].chengke[k].xingming);
strcpy(t[i].chengke[k-1].zhengjianhao,t[i].chengke[k].zhengjianhao);
t[i].chengke[k-1].dingpiaoshu=t[i].chengke[k].dingpiaoshu;
strcpy(t[i].chengke[k-1].hangbanhao,t[i].chengke[k].hangbanhao);
}
t[i].sit--;
}
printf("��Ʊ�ɹ�!!\n");//��ʾ��Ʊ�ɹ�
}
}

//�޸ĺ�����Ϣ
void channge(HANGBAN t[],int n)
{
char s[20];//Ҫ�޸ĳ˿͵�����
int i,j;
printf("��������Ҫ�޸ĵĺ����:");//��ʾ��Ϣ
scanf("%s",s);//���뺽����
for(i=0;i<n;i++)//�ӵ�һ����¼��ʼ��ֱ�����һ��
{
if(strcmp(s,t[i].hangbanming)==0)//��¼�еĺ���������Ҫ���ҵĺ����Ƿ����
break;//��ȣ��������
}
if(i>n-1)//û�ҵ�
printf("-------------------------�ܱ�Ǹ��û���ҵ���Ҫ�ҵĺ���-------------------------------\n");
else
{
printf("--------------------------------------------------------------------------------------\n");
printf("������    ��ɳ���   �������        ����ʱ��         ����ʱ��    ʣ�µ���λ   �۸�    �ۿ�\n");//�ҵ�����ʾԭ�ȼ�¼
printf("%-12s%-12s%-12s%-12s%-14s%-10d%-8s%-10s\n",t[i].hangbanming,t[i].qifeichengshi,t[i].jiangluochengshi,t[i].qifeishijian,t[i].jiangluoshijian,t[i].zuoweishu,t[i].piaojia,t[i].zhekou);
printf("please input the new information:\n");
scanf("%s",t[i].hangbanming);//���뺽����
scanf("%s",t[i].qifeichengshi);//������ɳ���
scanf("%s",t[i].jiangluochengshi);//���뽵�����
scanf("%s",t[i].qifeishijian);//�������ʱ��
scanf("%s",t[i].jiangluoshijian);//���뽵��ʱ��
scanf("%d",t[i].zuoweishu);//������λ��
scanf("%s",t[i].piaojia);//����Ʊ��
scanf("%s",t[i].zhekou);//�����ۿ�
}
}

void main()
{
int i;
HANGBAN flight[Q];
int length;//�����¼����
for(i=0;i>-1;i++)
{
switch(menu_select())//�������˵�����������ֵ������������������
{
case 0:length=enter(flight);break;
case 1:list(flight,length);break;
case 2:search1(flight,length);break;
case 3:search2(flight,length);break;
case 4:book(flight,length);break;
case 5:quit(flight,length);break;
case 6:channge(flight,length);break;
case 7:save(flight,length);break;
case 8:exit(0);//�˳����������
}
}
}