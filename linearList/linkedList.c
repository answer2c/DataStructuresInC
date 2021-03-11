//
// Created by ybc on 2021/1/21.
//
#include "../common.h"

typedef struct LNode  *Ptr;
struct LNode{
    ElementType data;
    Ptr next;
};

Ptr initList() {
    Ptr L = (Ptr) malloc(sizeof(struct LNode));
    L->next = NULL;
    return L;
}

/**
 * 头插
 * @param L
 * @param n
 * @return
 */
int insert(Ptr L, ElementType n) {
    Ptr newNode = (Ptr) malloc(sizeof(struct LNode));
    newNode->data = n;
    newNode->next = L->next;
    L->next = newNode;
    return OK;
}


Ptr findPrevious(Ptr L , Ptr Position) {
    Ptr p = L;
    while (p->next != NULL) {
        if (p->next == Position) {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

int isEmpty(Ptr L){
    return L->next == NULL;
}

int delete(Ptr L, Ptr position) {
    if (isEmpty(L)) {
        return ERROR;
    }
    Ptr pre = findPrevious(L, position);
    pre->next = position->next;
    free(position);
    position = NULL;
    return OK;
}

int destructList(Ptr L) {
    Ptr p = L->next;
    while (p) {
        Ptr next = p->next;
        free(p);
        p = next;
    }
    free(L);
    return OK;
}


void printList(Ptr L) {
    Ptr p = L->next;
    if (p == NULL) {
        printf("--empty list--\n");
    }
    printf("----\n");
    while (p) {
        printf("%d \n", p->data);
        p = p->next;
    }
    printf("----\n");
}

int main() {
    Ptr L = initList();
    insert(L,3);
    insert(L,9);
    insert(L,10);
    insert(L,1);
    printList(L);
    delete(L, L->next->next);
    printList(L);
    destructList(L);
    return 0;
}