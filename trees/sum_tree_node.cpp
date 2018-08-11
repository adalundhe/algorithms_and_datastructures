#include <iostream>

template <typename T>
struct Node{
  T data;
  Node<T> *left, *right;
};

template <typename T>
Node<T> * create_node(T data){
  Node<T> *new_node = new Node<T>;

  new_node->data = data;
  new_node->left = nullptr;
  new_node->right = nullptr;

  return new_node;
}

template <typename T>
int sum(Node<T> *root){
  if(root == nullptr)
    return 0;
  return (root->data + sum(root->left) + sum(root->right));
}


int main(){

  Node<int> *root = new Node<int>;
  root->data = 1;

  root->left = create_node(2);
  root->right = create_node(3);
  root->left->left = create_node(4);
  root->left->right = create_node(5);
  root->right->left = create_node(6);
  root->right->right = create_node(7);

  int result = sum(root);

  std::cout<<"Got: "<<result<<std::endl;

  return 0;
}
