  #ifndef RHTREE_HPP
#define RHTREE_HPP

struct node {
  int ele;
  node* left;
  node* right;
  node(int e):left(0), right(0){
    ele = e;
  }
};

class RHTree
{
public:
	RHTree();
	~RHTree();
	void inOrder(node* );
	void preOrder(node* );
	void postOrder(node* );
	void insert(int ele); 
	node* getRoot();
private:
	node* root;
};

#endif