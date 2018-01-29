#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"tree.h"
#define MAXI 50
int main() {
    BN* root;
    BN* que[MAXI];    /*used for free*/
    int head = 0;   /*head of que*/
    int tail = 1;   /*tail of que*/
    buildTree(&root);
    outputTree(root);
    /*the free procedure*/
    que[0] = root;
    while (head != tail) {
        if (que[head]->left != NULL) {
            que[tail] = que[head]->left;
            tail = (tail + 1) % MAXI;
        }
        if (que[head]->right != NULL) {
            que[tail] = que[head]->right;
            tail = (tail + 1) % MAXI;
        }
        free(que[head]);
        head = (head + 1) % MAXI;
    }
    return 0;
}