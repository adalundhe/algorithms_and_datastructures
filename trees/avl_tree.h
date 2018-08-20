#ifndef __AVL_TREE_H_INCLUDES__
#define __AVL_TREE_H_INCLUDES__
#include <stack>
#include <iostream>

template <typename T>
struct Node{
  T data;
  int height=1;
  Node<T> *left=nullptr, *right=nullptr;
};

template <typename T>
class AVLTree{
  public:
    AVLTree();
    void insert(T data);
    T find(T query);
    void remove(T data);
    void print();
  private:
    Node<T> *root = nullptr;
    int height(Node<T> *node);
    int max(int a, int b);
    Node<T>* left_rotate(Node<T> *left);
    Node<T>* right_rotate(Node<T> *right);
    int get_balance(Node<T> *node);
    Node<T>* insert_node(Node<T> *node, T data);
    Node<T>* delete_node(Node<T>* node, T data);
    Node<T>* min_value_node(Node<T>* node);
};

template <typename T>
AVLTree<T>::AVLTree(){};

template <typename T>
T AVLTree<T>::find(T query){

  std::stack<Node<T>*> node_stack;
  node_stack.push(root);

  while(!node_stack.empty()){

    Node<T>* current = node_stack.top();
    node_stack.pop();

    if(current->data == query)
      return current->data;

    if(current->left != nullptr)
      node_stack.push(current->left);
    if(current->right != nullptr)
      node_stack.push(current->right);

  }

  return T();
}

template <typename T>
void AVLTree<T>::insert(T data){
  Node<T>* start = root;
  root = insert_node(root, data);
}

template <typename T>
void AVLTree<T>::print(){
  std::stack<Node<T>*> node_stack;
  node_stack.push(root);
  Node<T>* current;

  while(!node_stack.empty()){
    current = node_stack.top();
    node_stack.pop();

    std::cout<<"Node of height: "<<current->height<<" with data: "<<current->data<<std::endl;

    if(current->left)
      node_stack.push(current->left);
    if(current->right)
      node_stack.push(current->right);

  }

}

template <typename T>
Node<T>* AVLTree<T>::insert_node(Node<T>* node, T data){
  if(node == nullptr){
    Node<T> *new_node = new Node<T>;
    new_node->data = data;
    return new_node;
  };

  if(data < node->data)
    node->left = insert_node(node->left, data);
  else if(data > node->data)
    node->right = insert_node(node->right, data);
  else
    return node;

  node->height = max(height(node->left), height(node->right)) + 1;

  int balance = get_balance(node);

  if(balance > 1 && data < node->left->data)
    return right_rotate(node);

  if(balance < -1 && data > node->right->data)
    return left_rotate(node);

  if(balance > 1 && data > node->left->data){
    node->left = left_rotate(node->left);
    return right_rotate(node);
  }

  if(balance < -1 && data < node->right->data){
    node->right = right_rotate(node->right);
    return left_rotate(node);
  }

  return node;

}

template <typename T>
void AVLTree<T>::remove(T data){
  Node<T>* start = root;
  root = delete_node(start, data);
}

template <typename T>
Node<T>* AVLTree<T>::delete_node(Node<T>* node, T data){
  if(node == nullptr)
    return node;

  if(data < node->data)
    node->left = delete_node(node->left, data);
  else if(data > node->data)
    node->right = delete_node(node->right, data);
  else{
    if(node->left == nullptr || node->right == nullptr){

      Node<T>* temp = node->left ? node->left : node->right;

      if(temp == nullptr){
        temp = node;
        node = nullptr;
      }
      else
        *node = *temp;

      free(temp);

    }
    else{
      Node<T>* temp = min_value_node(node->right);
      node->data = temp->data;
      node->right = delete_node(node->right, temp->data);
    }
  }

  if(node == nullptr)
    return node;

  node->height = max(height(node->left), height(node->right)) + 1;

  int balance = get_balance(node);

  if(balance > 1 && get_balance(node->left) >= 0)
    return right_rotate(node);

  if(balance > 1 && get_balance(node->left) < 0){
    node->left = left_rotate(node->left);
    return right_rotate(node);
  }

  if(balance < -1 && get_balance(node->right) <= 0)
    return left_rotate(node);

  if(balance < -1 && get_balance(node->right) > 0){
    node->right = right_rotate(node->right);
    return left_rotate(node);
  }

  return node;

}

template <typename T>
Node<T>* AVLTree<T>::min_value_node(Node<T>* node){
  Node<T>* current = node;

  while(current->left != nullptr)
    current = current->left;

  return current;
}

template <typename T>
int AVLTree<T>::height(Node<T> *node){
  if(node == nullptr)
    return 0;
  return node->height;
}

template <typename T>
int AVLTree<T>::max(int a, int b){
  return (a > b) ? a : b;
}

template <typename T>
Node<T>* AVLTree<T>::left_rotate(Node<T> *left){
  Node<T> *right_child = left->right;
  Node<T> *right_left_child = right_child->left;

  right_child->left = left;
  left->right = right_left_child;

  left->height = max(height(left->left), height(left->right)) + 1;
  right_child->height = max(height(right_child->left), height(right_child->right)) + 1;

  return right_child;
}

template <typename T>
Node<T>* AVLTree<T>::right_rotate(Node<T> *right){
  Node<T> *left_child = right->left;
  Node<T> *left_right_child = left_child->right;

  left_child->right = right;
  right->left = left_right_child;

  right->height = max(height(right->left), height(right->right));
  left_child->height = max(height(left_child->left), height(left_child->right));

  return left_child;
}

template <typename T>
int AVLTree<T>::get_balance(Node<T> *node){
  return height(node->left) - height(node->right);
}

#endif
