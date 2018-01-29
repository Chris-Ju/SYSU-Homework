#include <stdio.h>
#include "stack.h"

int main() {
    Node *top = NULL;
    int t, n, pop_num;

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        push(&top, n);  // 压栈
    }

    scanf("%d", &t);
    while (t--) {
        pop_num = pop(&top);  // 出栈，并接收出栈的值
        printf("%d ", pop_num);  // 输入该值
    }
    printf("\n");

    if (top)
        del(&top);  // free剩余节点

    return 0;
}

