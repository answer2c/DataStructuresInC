#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define OK 1

//栈
typedef int ElementType;
typedef struct SNode *stack;

struct SNode {
    ElementType *data;
    int top;
    int maxsize;
};

stack initStack() {
    int size;
    printf("请输入栈的大小:");
    scanf("%d", &size);
    stack L = (stack) malloc(sizeof(struct SNode));
    L->data = (ElementType *) malloc(sizeof (ElementType) * size);
    L->top = -1; //空栈
    L->maxsize = size;
    return L;
}

int push(stack L) {
    ElementType i;
    printf("give me the number which u wanner push: ");
    scanf("%d", &i);
    if (L->top >= L->maxsize - 1) {
        return ERROR;
    }
    L->top++;
    *(L->data + L->top) = i;
    return OK;
}

ElementType pop(stack L) {
    if (L->top < 0) {
        return ERROR;
    }

    ElementType res = *(L->data + L->top);
    L->top--;
    return res;
}

int clearStack(stack L) {
    free(L->data);
    L->data = NULL;
    free(L);
    L = NULL;
    return OK;
}

int main() {
    int move;
    stack L = initStack();


    while (1) {
        printf("请输入你要执行的操作: 1入栈 2出栈 3退出 \n");
        scanf("%d", &move);
        switch (move) {
            case 1:
                if (push(L) != OK) {
                    printf("入栈失败\n");
                } else {
                    printf("入栈成功\n");
                }
                break;
            case 2:
                printf("%d \n", pop(L));
                break;
            case 3:
            default:
                clearStack(L);
                return 0;
        }
    }

}