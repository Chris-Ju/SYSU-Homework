#ifndef BT_TREE
#define BT_TREE
#include <iostream>
using namespace std;
struct node {
  int ele;
  node* left;
  node* right;
  node(int e):left(0), right(0){
    ele = e;
  }
};
class BinaryTree {
  private:
    node* root;
    void MemoryDelete(node* p);
    static void BuildTree(const node* Source_Root, node* &Target_Root);
    static void BuildTree(const int* arr,int len, node* &root);
    static void preorder(const node* p);
  public:
    BinaryTree();
    BinaryTree(const BinaryTree&);
    BinaryTree(const int* arr, int len);
    void ResetTree(const int* arr, int len);
    ~BinaryTree();
    void clear();
    void insert(int ele);
    void Delete(int ele);
    void print();
};
#endif