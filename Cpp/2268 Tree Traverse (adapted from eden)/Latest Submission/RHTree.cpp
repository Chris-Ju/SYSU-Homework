  #include "RHTree.hpp"
#include <iostream>
using std::cout;

void del(node* p)
{
    if(p->left == NULL && p->right == NULL)
    {
        delete p;
        return;
    }
    if(p->left != NULL)
        del(p->left);
    if(p->right != NULL)
        del(p->right);
    delete p;
    return;
}

RHTree::RHTree()
{
    root = NULL;
}


RHTree::~RHTree()
{
    if(root == NULL)
        return;
    del(root);
    root = NULL;
}

node* RHTree::getRoot()
{
    return root;
}

void RHTree::inOrder(node* root)
{
    if(root == NULL)
        return;
    inOrder(root->left);
    cout << " " <<  root->ele;
    inOrder(root->right);
}

void RHTree::preOrder(node* root)
{
    if(root == NULL)
        return;
    cout << " " <<  root->ele;
    preOrder(root->left);
    preOrder(root->right);
}

void RHTree::postOrder(node* root)
{
    if(root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout << " " <<  root->ele;
}


void RHTree::insert(int ele)
{
    if(root == NULL)
    {
        root = new node(ele);
        return;
    }
    node* current = root;
    node* addone = new node(ele);
    while(true)
    {
        
        if(current->ele >= ele)
        {
            if(current->left == NULL)
            {
                current->left = addone;
                return;
            }
            else
                current = current->left;
        }
        else if(current->ele < ele)
        {
            if(current->right == NULL)
            {    
                current->right = addone;
                return;
            }
            else
                current = current->right;
        }
    }
}

