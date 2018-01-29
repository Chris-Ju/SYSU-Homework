#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <stdlib.h>

void push(Node **top, int n)
{
    Node* add = (Node *)malloc(sizeof(Node));
    add->num = n;
    add->next = (*top);
    *top = add;
}

int pop(Node **top)
{
    if((*top) == NULL)
        return -1;
    int num = (*top)->num;
    Node* current = *top;
    (*top) = (*top)->next;
    free(current);
    return num;
}

void del(Node **top)
{
    if((*top) == NULL)
        return;
    del(&((*top)->next));
    free(*top);
}

#endif // STACK_H
