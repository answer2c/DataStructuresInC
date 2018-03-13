#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1;
#define ERROR -1;
#define OVERFLOW -2;

typedef int Status;

const int LIST_SIZE=20;
//学生结构体
typedef struct{
	int num; 
	char name[20];

}stu;

//顺序表结构体
typedef struct{
	stu *elem;
	int length;
	int ListSize;

}sqlist;

/**
*初始化顺序表
**/
Status  InitList(sqlist *L){
	if(L==NULL){
		return ERROR;
	}

	L->elem=(stu *)malloc(sizeof(stu)*LIST_SIZE);
	L->length=0;
	L->ListSize=LIST_SIZE;

	return OK;

}

/**
* 销毁顺序表
*/

Status DesList(sqlist *L ){
	if(L->elem){
		free(L->elem);}
		L->elem=NULL;
	
	return OK;
}


/**
*  录入学生信息
*
*/

void Insert(sqlist *L,int n){
	int i;
	printf("请依次输入学生信息");
	for(i=0;i<n;i++){
		printf("第%d个学生信息：\n学号：",i+1);
		scanf("%d",&L->elem[i].num);
		printf("姓名：");
		scanf("%s",L->elem[i].name);
	}
	L->length=n;
}


/**
*查找学生是否存在
*/
Status Locate(sqlist L,int n){
	int i=1;
	//return L.elem[2].num;
	while(i<=L.length&&n!=L.elem[i-1].num){
		i++;
	}
	if(i>L.length){
		return 0;
	}else return i;

}


/**
*插入一条学生信息
*
*/
Status Insert_stu(sqlist *L,int i,stu s){
	int n=L->length-1;
	//合法性检查

	if(i<1||i>L->length+1){
		return ERROR;	
	}
	if(L->length>=LIST_SIZE){
		return OVERFLOW;
	 }
	
	for(;n>=i-1;n--){
		L->elem[n+1]=L->elem[n];		
	}
	L->elem[i-1]=s;
	L->length++;

	return OK;

}


/**
*删除一条学生信息
*/
Status Del_stu(sqlist *L,int i){
	int q=i-1;
	if(L->length==0||i<1||i>L->length)
	{  return ERROR;}

	for(q;q<L->length-1;q++){
		L->elem[q]=L->elem[q+1];
	}
	L->length--;
	return OK;

}


/**
*输出所有学生信息
*/
void show_stu(sqlist L){
	int i=0;
	if(L.length<1){
		printf("学生信息为空!\n");
		return;
	}
	for(;i<L.length;i++){
		printf("第%d名学生：姓名%s  学号：%d \n",i+1,L.elem[i].name,L.elem[i].num);
	
	}


}



typedef struct{
	int sz[10];
	int number;
	int age;
}cla;
int main(){

	int m;	stu ns;int j; int k;int h=1;
	sqlist L;
	InitList(&L);
	printf("***欢迎使用学生信息管理系统***\n");

	while(h==1){
		printf("请选择您要执行的操作：\n");
		printf("输入学生信息[1]；插入学生信息[2] ；\n查找学生信息[3]；输出所有学生信息[4]；\n删除学生信息[5]；退出 [6]\n");
		scanf("%d",&m);
		switch(m){
		case 1:printf("学生人数：");scanf("%d",&j);
			   if(j>LIST_SIZE){
					printf("学生人数超过限制\n");	
					break;
				}
			   Insert(&L,j);break;
			case 2:
					ns.num=20;
					strcpy(ns.name,"yyy");
					Insert_stu(&L,3,ns);break;
			case 3: printf("输入要查找的学生学号"); scanf("%d",&k);printf("%d",Locate(L,k));break;
			case 4:show_stu(L);break;
			case 5:printf("输入要删除学生的学号：");scanf("%d",&k);Del_stu(&L,k);break;
			case 6:	DesList(&L);h=-1;break;
			default:DesList(&L);h=-1;break;
		}
	
	}


	
	system("pause");
	return 0;
}
