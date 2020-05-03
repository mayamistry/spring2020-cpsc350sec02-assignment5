#include "TreeNode.h"

template <class T>
class BST {
public:
  BST();
  ~BST();

  void insert(int k, T* value); //insert based on value
  T* search(int value);
  bool deleteNode(int k); //delete using the key here

  bool isEmpty();
  TreeNode<T>* getMin();
  TreeNode<T>* getMax();

  TreeNode<T>* getSuccessor(TreeNode<T> *d);
  void printTree(TreeNode<T> *node);

  TreeNode<T>* getRootNode();

  //create a method that traverses through the entire tree and just returns the node
  T* traverse(TreeNode<T>* node);


private:
  TreeNode<T> *root;
};

template <class T>
BST<T>::BST() {
  root = NULL;
}

template <class T>
BST<T>::~BST() {
  delete root;
}

//Big O of this is N (linear)
template <class T>
void BST<T>::printTree(TreeNode<T> *node) {
  //assuming we're using inOrder traversal
  if (node == NULL) {
    return;
  }
  printTree(node->left);
  cout << node->key << endl;
  printTree(node->right);
}

//big o of this is log n if balanced and if unbalanced Big O of N
template <class T>
TreeNode<T>* BST<T>::getMax() {
  //go all the way to the right of the tree since key == value
  TreeNode<T> *curr = root;
  if (root == NULL) {
    return NULL; //since tree is empty
  }
  while (curr->right != NULL) { //check if the right of curr is not NULL
    curr = curr->right;
  }
  return curr; //you could return node or value inside, whatever works
}

template <class T>
TreeNode<T>* BST<T>::getMin() {
  //go all the way to the left of the tree since key == value
  TreeNode<T> *curr = root;
  if (root == NULL) {
    return NULL; //since
  }
  while (curr->left != NULL) {
    curr = curr->left;
  }
  return curr;
}
//do method for getMin since it's the opposite of getMax

template <class T>
bool BST<T>::isEmpty() {
  if (root == NULL) {
    return true;
  } else {
    return false;
  }
}

template <class T>
void BST<T>::insert(int k, T* value) {

  //we could search and make sure that the key we're inserting doesn't
  //already exist in the tree by calling the search function

  TreeNode<T> *node = new TreeNode<T>(k, value);
  if (isEmpty()) {
    root = node; //first node in tree since it would initially be empty
  } else {
    //not an empty tree
    TreeNode<T> *curr = root; //start at root
    TreeNode<T> *parent;
    while (curr != NULL) {
      parent = curr;
      if (k < curr->key) {
        //go left
        curr = curr->left;
        if (curr == NULL) {
          //found a leaf node
          //insert here
          parent->left = node;
          break;
        }
      } else {
        //go right
        curr = curr->right;
        if (curr == NULL) {
          parent->right = node;
          break;
        }
      }
    }
  }
}

//return type can vary, return whatever you want it to
template <class T>
T* BST<T>::search(int value){
  TreeNode<T> *curr = root;
  if (isEmpty()) {
    return NULL;
  } else {
    //tree is not isEmpty
    while(curr->key != value) {
      if (value < curr->key) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
      if (curr == NULL) {
        //didn't find the value
        return NULL;
      }
    }
  }
  return curr->value; //we found the node
}

template <class T>
bool BST<T>::deleteNode(int k){
  //first need to check if it exists
  //need to check if: has one child, two children, or a leaf node
  if (isEmpty()) {
    return false;
  }

  TreeNode<T> *parent = root;
  TreeNode<T> *curr = root;
  bool isLeft = true;

  while (curr->key != k) {
    parent = curr;
    if (k < curr->key) {
      //go left
      isLeft = true;
      curr = curr->left;
    } else {
      //go right
      isLeft = false;
      curr = curr->right;
    }
    if (curr == NULL) {
      return false;
    }
  }

  //if we make it here, then we found the value so let's start to delete
  if (curr->left == NULL && curr->right == NULL) {
    //then we have a leaf TreeNode
    //first check, is it the root, leftnode, or right node?
    if (curr == root) {
      //only one node in the TreeNode
      root = NULL; //null out the only pointer
    } else if (isLeft) {
      //node is left
      parent->left = NULL;
    } else {
      //node is right
      parent -> right = NULL;
    }
    //one child case
  } else if (curr->right == NULL) {
    //node we're deleting has one child but it's not on the right so must be left child
    if (curr == root) {
      root = curr->left;
    } else if (isLeft) {
      //to the left
      parent->left = curr->left;
    } else {
      //to the right
      parent->right = curr->left;
    }
  } else if (curr->left == NULL) {
    //node we're deleting has no left child, so we have a right child
    //these branch statements identify the position of node to be deleted
    if (curr == root) {
      root = curr->right;
    } else if (isLeft) {
      //to the left
      parent->left = curr->right;
    } else {
      //to the right
      parent->right = curr->right;
    }
  } else {
    //the node to be deleted has two children
    TreeNode<T> *successor = getSuccessor(curr);

    if (curr == root) {
      root = successor;
    } else if (isLeft) {
      parent->left = successor;
    } else {
      parent->right = successor;
    }

    //link successor to d's left child
    successor->left = curr->left;
  }
  return true;
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d) {
  //the parameter d represents the node to be deleted
  TreeNode<T> *curr = d->right; //go the right of the node you're deleting
  TreeNode<T> *sp = d; //successor of parent
  TreeNode<T> *successor = d;

  while (curr != NULL) {
    sp = successor;
    successor = curr;
    curr = curr->left;
  }
  if (successor != d->right) {
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}

template <class T>
T* traverse(TreeNode<T>* node) {
  if (node == NULL) {
    return NULL;
  }
  traverse(node->left);
  return node->value;
  traverse(node->right);
}


template <class T>
TreeNode<T>* BST<T>::getRootNode() {
  return root;
}
