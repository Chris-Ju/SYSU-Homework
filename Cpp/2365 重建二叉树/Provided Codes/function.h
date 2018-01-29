#ifndef FUNCTION_H
#define FUNCTION_H

#include "TreeNode.h"
#include <malloc.h>
#include <stdlib.h>

TreeNode* reConstructBinaryTree(int pre[], int in[], int size)
{
    if(size == 0)
        return NULL;
    int index;
    for(int i = 0; i < size; i++)
    {
        if(pre[0] == in[i])
        {
            index = i;
            break;
        }
    }
    TreeNode* root = (TreeNode *)malloc(sizeof(TreeNode));
    root->val = pre[0];
    root->left = reConstructBinaryTree(pre + 1, in, index);
    root->right = reConstructBinaryTree(pre + index + 1, in + index + 1, size - index - 1);
    return root;
}
void deleteTree(TreeNode* root)
{
    if(root == 0)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

#endif
