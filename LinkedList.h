#include "ListNode.h"

//template class
template <class T>
class LinkedList {
  public:
    LinkedList();
    ~LinkedList();

    void insertFront(T data);
    void insertBack(T data);
    T removeFront();
    int search(T val); //returns the position of the node we are looking for
    void remove(T val); //removes wherever the node is using
    //NEED TO DRAW THIS OUT LATER TO MAKE IT WORK
    void removeAtPos(int pos);

    unsigned int getSize();
    bool isEmpty();
    void printList();

    ListNode<T> *front;
    unsigned int size;
};

//implementation goes here
template <class T>
LinkedList<T>::LinkedList() {
  front = NULL;
  size = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
  front = NULL;
  delete front;
}

template <class T>
unsigned int LinkedList<T>::getSize() {
  return size;
}

template <class T>
bool LinkedList<T>::isEmpty() {
  return (size == 0);
}

template <class T>
void LinkedList<T>::printList() {
  ListNode<T> *curr = front;

  while(curr != NULL) {
    cout << curr->data << endl;
    curr = curr->next;
  }
}

template <class T>
void LinkedList<T>::insertFront(T data) {
  ListNode<T> *node = new ListNode<T>(data);
  node->next = front;
  front = node;
  ++size;
}

template <class T>
void LinkedList<T>::insertBack(T data) {
  ListNode<T> *node = new ListNode<T>(data);
  ListNode<T> *curr = front;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  if (isEmpty()) {
    front = node;
  } else {
    curr->next = node;
  }
  ++size;
}

template <class T>
T LinkedList<T>::removeFront() {
  if (isEmpty()) {
    cout << "List is already empty." << endl;
    return 1;
  }

  T temp = front->data;
  ListNode<T> *ft = front;
  front = front->next;
  ft->next = NULL;
  delete ft;
  --size;

  return temp;
}

template <class T>
int LinkedList<T>::search(T val) {
  int pos = -1;
  ListNode<T> *curr = front;
  while (curr != NULL) {
    ++pos;
    if (curr->data == val) { //is this the right thing we're trying to remove?
      //found it!
      break;
    } else {
      //didn't find it so continue
      curr = curr->next;
    }
  }
  if (curr == NULL) {
    //didn't find it after iterating through the whole thing
    pos = -1;
  }
  return pos;
}

template <class T>
void LinkedList<T>::remove(T val) {
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;


  while (curr != NULL) {
    //loop until I find the position
    prev = curr;
    curr = curr->next;
    if (val == curr->data) {
      break;
    }
  }

  if (curr == NULL) {
    cout << "Didn't find the node that needs to removed from list." << endl;
    return;
  }
  //continue with actual deletion process
  prev->next = curr->next;
  curr->next = NULL;
  T temp = curr->data;
  delete curr;
  size--;
}

template <class T>
void LinkedList<T>::removeAtPos(int pos){
  //error checking to make sure pos does not exceed size of ListNode
  int idx = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;
  while(idx != pos){
    //loop until I find the position
    prev = curr;
    curr = curr->next;
    idx++;
  }
  //if the node getting deleted is the last node
  //if the node getting deleted is the front node
  if (isEmpty()) {
    cout << "Can't remove since list is empty. " << endl;
    return;
  } else if (size == 1) {
    curr->next = NULL;
  } else if (pos == 0) {
    front = front->next;
    curr->next = NULL;
  } else if (pos == size - 1) {
    prev->next = NULL;
  } else {
    prev->next = curr->next;
    curr->next = NULL;
  }
  //now lets continue w the deletion processing

  //front = curr->next;
  T temp = curr->data;
  delete curr;
  size--;
}
