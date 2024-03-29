#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
Node* init_root(int value)
{
	return create_node(value);
}
Node* create_node(int value)
{
	Node *node=(Node *)malloc(sizeof(Node));
	node->left=NULL;
	node->right=NULL;
	node->value=value;
	return node;
}
void insert_node(Node *p, int value)
{
	if((p->value) > value)
    {
        if(p->left==NULL)
            p->left=create_node(value);
        else
            insert_node(p->left,value);
    }
	else if((p->value) < value)
    {
        if(p->right==NULL)
	        p->right=create_node(value);
        else
            insert_node(p->right,value);
    }
}
void traverse_tree_inorder(Node *p)
{
	if(p!=NULL)
	{
		traverse_tree_inorder(p->left);
		printf("%d ",p->value);
		traverse_tree_inorder(p->right);
	}
}
void recycle_nodes(Node *p)
{
	if(p->left!=NULL)
		recycle_nodes(p->left);	
	if(p->right!=NULL)
		recycle_nodes(p->right);
	free(p);
	return;
}
