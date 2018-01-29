 #include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node {
    int x;
    struct node* left;
    struct node* right;
}BN;


void buildTree(BN** rootptr)
{
    int num, tot = 1, head = 1;
    BN* a[50];
    scanf("%d", &num);
    BN* p = (BN*)malloc(sizeof(BN));
    *rootptr = p;
    (*rootptr) -> x = num;
    a[1] = *rootptr;
    a[1] -> left = NULL;
    a[1] -> right = NULL;
    while (num != -1) {
        scanf("%d", &num);
        if (num != -1) {
            tot++;
            BN* left = (BN*)malloc(sizeof(BN));
            left -> x = num;
            left -> left = NULL;
            left -> right = NULL;
            a[tot] = left;
            a[head] -> left = left;
            scanf("%d", &num);
        }
        if (num != -1) {
            tot++;
            BN* right = (BN*)malloc(sizeof(BN));
            right -> x = num;
            right -> right = NULL;
            right -> left = NULL;
            a[tot] = right;
            a[head] -> right = right;
        }
        head++;
    }
}

void outputTree(BN* root)
{
    if (root -> left != NULL) {
        outputTree(root -> left);
    }
    printf("%d ", root -> x);
    if (root -> right != NULL) {
        outputTree(root -> right);
    }
}
