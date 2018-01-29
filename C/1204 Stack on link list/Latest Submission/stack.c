#include<stdlib.h>
#include"stack.h"
void push(Stack *stack, int value)
{
  	stack->top=createNode(value,&(stack->top));
  	stack->size++;
}
void pop(Stack *stack)
{
    Node *pre=stack->top->next;
  	free(stack->top);
  	stack->top=pre;
    (stack->size)--;
}
int top(Stack *stack)
{
  	return (stack->top->data);
}
int size(Stack *stack)
{
    return (stack->size);
}
int empty(Stack *stack)
{
    if(stack->size)
  		return 0;
  	return 1;
}