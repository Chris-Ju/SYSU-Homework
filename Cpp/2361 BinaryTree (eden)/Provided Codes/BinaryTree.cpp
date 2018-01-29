#include "BinaryTree.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <cstring>

BinaryTree::Node* buildTree(std::string, std::string);


void del(BinaryTree::Node* n)
{
	if(n == NULL)
		return;
	del(n->left);
	del(n->right);
	delete n;
	n = NULL;
}
BinaryTree::Node* BinaryTree::copyNode(BinaryTree::Node * oldNode, BinaryTree::Node * newNode)
{
	if(oldNode == NULL)
    {
        newNode = NULL;
        return NULL;
    }
	newNode = new Node(oldNode->val);
	newNode->left = copyNode(oldNode->left, newNode->left);
	newNode->right = copyNode(oldNode->right, newNode->right);
	return newNode;
}

BinaryTree::BinaryTree(const BinaryTree& n)
{
    root = new Node(n.getRoot()->val);
	root->left = copyNode(n.getRoot()->left, root->left);
    root->right = copyNode(n.getRoot()->right, root->right);
}

BinaryTree::BinaryTree(std::vector<char>& n)
{
    if(n.empty())
    {
        root = NULL;
        return;
    }
    root = new Node(n.front());
    BinaryTree::Node* k[100];
    int head = 0, tail = 1;
    k[0] = root;
    std::vector<char> m = n;
    m.erase(m.begin());
    while(!m.empty())
    {
        if(k[head]->val == EMPTY_ELE)
        {
            head++;
            continue;
        }
        k[head]->left = new BinaryTree::Node(m.front());
        k[tail++] = k[head]->left;
        m.erase(m.begin());
        if(m.empty())
            return;
        k[head]->right = new BinaryTree::Node(m.front());
        k[tail++] = k[head]->right;
        m.erase(m.begin());
        head++;
    }
}

BinaryTree& BinaryTree::operator=(const BinaryTree& n)
{
	if(n.getRoot() == root)
        return *this;
    clear();
    root = new Node(n.getRoot()->val);
	root->left = copyNode(n.getRoot()->left, root->left);
    root->right = copyNode(n.getRoot()->right, root->right);
	return *this;
}

BinaryTree::Node* BinaryTree::getRoot() const
{
	return root;
}
void BinaryTree::clear()
{
	del(root);
}

BinaryTree::~BinaryTree()
{
    clear();
}

BinaryTree::BinaryTree(const std::vector<char>& preOrder,const std::vector<char>& inOrder)
{
    std::vector<char> pre;
    std::vector<char> in;
    pre.assign(preOrder.begin(), preOrder.end());
    in.assign(inOrder.begin(), inOrder.end());
    char m[100], n[100];
    memset(m, 0, sizeof(m));
    memset(n, 0, sizeof(n));
    for(int i = 0; i < pre.size(); i++)
    {
        m[i] = pre.at(i);
        n[i] = in.at(i);
    }
    std::string k = m, l = n;
    root = buildTree(k, l);
}


BinaryTree::Node* buildTree(std::string pre, std::string in)
{
    if(pre.length() == 0)
    {
        BinaryTree::Node* n = new BinaryTree::Node(EMPTY_ELE);
        return n;
    }
    char c = pre[0];
    BinaryTree::Node* root = new BinaryTree::Node(c);
    //if(pre.length() == 1)
        //return root;
    std::string prefirst, infirst, presecond, insecond;
    int index = in.find(c);
    infirst = in.substr(0, index);
    insecond = in.substr(index + 1);
    int clength = infirst.length();
    prefirst = pre.substr(1, clength);
    presecond = pre.substr(clength + 1);
    root->left = buildTree(prefirst, infirst);
    root->right = buildTree(presecond, insecond);
    return root;

}

void BinaryTree::preOrder(void (*visite)(BinaryTree::Node*), Node* m)
{
    if(m == NULL || m->val == EMPTY_ELE)
        return;
    (*visite)(m);
    preOrder(visite, m->left);
    preOrder(visite, m->right);

}

void BinaryTree::inOrder(void (*visite)(BinaryTree::Node*), Node* m)
{
    if(m == NULL || m->val == EMPTY_ELE)
        return;
    inOrder(visite, m->left);
    (*visite)(m);
    inOrder(visite, m->right);
}

void BinaryTree::postOrder(void (*visite)(BinaryTree::Node*), Node* m)
{
    if(m == NULL || m->val == EMPTY_ELE)
        return;
    postOrder(visite, m->left);
    postOrder(visite, m->right);
    (*visite)(m);
}
