#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR -1
#define OVERFLOW -2

typedef int STATUS;

const int LIST_SIZE = 20;
const int NAME_LEN = 20;

static int class_size;

//学生结构体
typedef struct {
	int no; //学号
	char name[NAME_LEN];
}student;

//顺序表结构体
typedef struct {
    student *elem;
    int length;
	int ListSize;
}sqlist;


void s_gets(char *str, int len)
{
    fgets(str, len, stdin);
    char *find;
    if ((find = strchr(str, '\n')) != NULL) {
        //把字符串最后的换行符换成空字符
        *find = '\0';
    } else {
        //处理调缓冲区的剩余字符
        while (getchar() != '\n')
            continue;
    }
}

/**
*初始化顺序表
**/
STATUS  initList(sqlist *L) {
	if (L == NULL) {
		return ERROR;
	}
	L->elem = NULL; 	// 一开始不分配空间s
    L->length = 0;
    L->ListSize = LIST_SIZE;
	return OK;
}

/**
* 销毁顺序表
*/
STATUS destructList(sqlist *L )
{
    if (L->elem) {
        free(L->elem);
    }
    L->elem = NULL; //把elem指向null
    return OK;
}


/**
*  录入学生信息
*/
STATUS initStudentList(sqlist *L)
{
    extern int class_size;
    printf("输入班级学生的总数量:");
    if (!scanf("%d", &class_size)){
        class_size = LIST_SIZE;
    }
    L->elem = (student *) malloc( sizeof(student) * class_size);
	printf("请依次输入学生信息: \n");
    for (int i = 0; i < class_size; i++) {
        printf("第%d个学生信息：\n学号：", i+1);
        scanf("%d", &(L->elem[i].no));
        fflush(stdin);
        printf("姓名：");
        s_gets(L->elem[i].name, NAME_LEN);
    }
	L->length = class_size;
    return OK;
}


/**
*查找学生是否存在
*/
int findStu(sqlist L)
{
    int no;
    printf("输入要查找的学生学号:");
    scanf("%d", &no);
    int i = 0;
    while (i < L.length && no != L.elem[i].no)
        i++;

    if (i >= L.length)
        return ERROR;

    return i;
}


/**
 *
 * @param L
 * @param position 要插入的位置
 * @return
 */
STATUS insertNewStu(sqlist *L)
{
    int position;
    printf("输入要插入的位置:");
    scanf("%d", &position);
    student stu;
    printf("输入学号:");
    scanf("%d", &stu.no);
    printf("输入姓名:");
    fflush(stdin);
    s_gets(stu.name, NAME_LEN);

	//合法性检查
	if (position < 1 || position > L->ListSize) {
	    printf("位置不合法 \n");
	    return ERROR;
	}
	if (L->length >= L->ListSize) {
	    printf("学员数量已满 \n");
	    return OVERFLOW;
	}

	L->elem = realloc(L->elem, sizeof(student) * (L->length + 1));
	L->elem[L->length] = stu;
	for (int n = L->length-1; n >= position - 1; n--) {
	    //移动插入位置之后的所有元素
		L->elem[n+1] = L->elem[n];
	}

	L->elem[position-1] = stu;
	L->length++;
	return OK;
}


/**
 * 删除学员
 * @param L
 * @return
 */
STATUS delStu(sqlist *L)
{
    int no;
    printf("输入要删除学生的学号:");
    scanf("%d", &no);
    int position = 0;
    while (position<L->length && L->elem[position].no != no)
        position++;

    if (position >= L->length)
        return ERROR;

    for (int q = position; q < L->length - 1; q++) {
        L->elem[q] = L->elem[q + 1];
    }
    L->elem = realloc(L->elem, sizeof(student) * (L->length - 1));
    L->length--;
    return OK;
}

/**
 * 输出所有学员信息
 * @param L
 */
void showStu(sqlist L)
{
	if (L.length<1) {
		printf("学生信息为空!\n");
		return;
	}
	for(int i=0; i<L.length; i++) {
		printf("第%d名学生：姓名%s  学号：%d \n",i+1,L.elem[i].name,L.elem[i].no);
	}
}


int main()
{
	int h=1;
	int op;
	sqlist L;
	if (!initList(&L)) {
	    printf("初始化学生结构失败 \n");
	    exit(EXIT_FAILURE);
	}

	printf("***欢迎使用学生信息管理系统***\n");
	while (h == 1) {
		printf("请选择您要执行的操作：\n");
		printf("输入学生信息[1]；插入学生信息[2] ；\n查找学生信息[3]；输出所有学生信息[4]；\n删除学生信息[5]；退出 [6]\n");
		scanf("%d", &op);
		switch (op) {
            case 1:
                initStudentList(&L);
                break;
            case 2:
                if (!insertNewStu(&L)) {
                    printf("插入失败\n");
                }
                break;
			case 3:
            {
                int position = findStu(L);
                if (position != ERROR) {
                    printf("姓名:%s \n", L.elem[position].name);
                } else {
                    printf("not found \n");
                }
            }
			    break;
			case 4:
			    showStu(L);
			    break;
			case 5:
			    if (!delStu(&L)) {
			        printf("插入失败");
			    }
			    break;
            default:
                destructList(&L);
			    h=-1;
			    break;
		}
	}
	return 0;
}
