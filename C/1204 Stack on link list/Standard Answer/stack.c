#include "stack.h"
#include <stdlib.h>
int top(Stack *stack) {
  if (stack->size) return stack->top->data;
  return -1;
}

void pop(Stack *stack) {
  if (stack->size) {
    --stack->size;
    Node *temp = stack->top;
    stack->top = temp->next;
    free(temp);
  }
}

void push(Stack *stack, int num) {
  ++stack->size;
  stack->top = createNode(num, stack->top);
}

int size(Stack *stack) { return stack->size; }

int empty(Stack *stack) {return stack->size == 0; }