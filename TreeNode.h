#include <iostream>
using namespace std;

//of type int
template <class T>
class TreeNode {
public:
  TreeNode();
  TreeNode(int k, T* v);
  //TreeNode(int k, <type> v);
  ~TreeNode();
  //virtual destructor ~TreeNode(); when using a template class

  int key;
  T* value;
  TreeNode<T> *left; //tree nodes have left and right pointers
  TreeNode<T> *right;
};

template <class T>
TreeNode<T>::TreeNode() {
  key = 0;
  value = NULL;
  left = NULL;
  right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(int k, T* v) {
  key = k;
  value = v;
  left = NULL;
  right = NULL;
}

template <class T>
TreeNode<T>::~TreeNode() {
  delete left;
  delete right;
  delete value;
}
