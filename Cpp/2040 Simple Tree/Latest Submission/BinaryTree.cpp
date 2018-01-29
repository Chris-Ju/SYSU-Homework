 #include "BinaryTree.hpp"
node* find(node* p, int ele);
void del(node* p);
void insert0(int ele, node* root);
void BuildTree0(node* , node*);

void BinaryTree::MemoryDelete(node* p)
{
    delete p;
}

void BinaryTree::BuildTree(const node* Source_Root, node* &Target_Root)
{
    if(Source_Root == NULL)
        return;
    node *newone = new node(Source_Root->ele);
    Target_Root = newone;
    BuildTree(Source_Root->left, Target_Root->left);
    BuildTree(Source_Root->right, Target_Root->right);
}

void BinaryTree::BuildTree(const int* arr,int len, node* &root)
{
    root = new node(arr[0]);
    int i;
    for(i = 1; i < len; i++)
        insert0(arr[i], root);

}

void BinaryTree::preorder(const node* p)
{
    if(p == NULL)
        return;
    cout << p->ele << " ";
    preorder(p->left);
    preorder(p->right);
}

BinaryTree::BinaryTree()
{
    root = NULL;
}

BinaryTree::BinaryTree(const BinaryTree &Source_Root)
{
	root = NULL;
    BuildTree(Source_Root.root, root);
}

BinaryTree::BinaryTree(const int* arr, int len)
{
    BuildTree(arr, len, root);
}

void BinaryTree::ResetTree(const int* arr, int len)
{
    this->clear();
    BuildTree(arr, len, this->root);
}

BinaryTree::~BinaryTree()
{
    clear();
}

void BinaryTree::clear()
{
    if(root == NULL)
        return;
    del(root);
    root = NULL;
}

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

void BinaryTree::insert(int ele)
{
    if(root == NULL)
    {
        root = new node(ele);
        return;
    }
    insert0(ele, root);
}

void BinaryTree::print()
{
    preorder(root);
    cout << endl;
}

void BinaryTree::Delete(int ele)
{
	if(find(root, ele) == NULL)
    {
        //cout << "Can't find " << ele << endl;
		return;
	}
    node* current = root;
    node* last = current;
    //cout << "Have deleted " << ele << endl;
    while(true)
    {
       	if(current->ele == ele)
            break;
        last = current;
        if(ele > current->ele)
			current = current->right;
		else
			current = current->left;
    }
    if(current->left == NULL)
    {  
		if(current->right == NULL)
        {
            if(current == root)
            {
                delete root;
                root = NULL;
                return;
            }
            delete current;
            if(last->ele > ele)
                last->left = NULL;
            else
                last->right = NULL;
            return;
        }
        node* needel = current->right;
        BuildTree0(needel,current);
        delete needel;
        return;
    }
    else
    {
        last = current->left;
        if(last->right == NULL)
        {
            current->left = last->left;
            current->ele = last->ele;
            delete last;
            return;
        }
        else
        {
            node *father = last;
            while(true)
            {
                if(last->right == NULL)
                {
                    if(father == last)
                    {
                    	current->ele = last->right->ele;
                    	delete last->right;
                    	last->right = NULL;
                    }
					father->right = last->left;
                    current->ele = last->ele;
                    delete last;
                    return;
                }
                father = last;
                last = last->right;
            }
        }
    }


}

node* find(node *p, int ele)
{
    if(p == NULL)
        return NULL;
    node* a = NULL;
    node* b = NULL;
    if(p->ele == ele)
        return p;
    if(p->left != NULL)
        a = find(p->left, ele);
    if(p->right != NULL)
        b = find(p->right, ele);
    if(a == NULL)
        return b;
    return a;

}

void insert0(int ele, node* root)
{
    if(find(root, ele) != NULL)
        return;
    node* current = root;
    node* addone = new node(ele);
    while(true)
    {
        
        if(current->ele > ele)
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

void BuildTree0(node* n, node* m)
{
    m->ele = n->ele;
    m->left = n->left;
    m->right = n->right;
}