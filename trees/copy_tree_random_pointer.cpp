#include <iostream>

template <typename T>
struct Node{
  T data;
  Node<T> *left, *right, *random;
};

template <typename T>
Node<T>* new_node(T node_data){
  Node<T>* new_node = new Node<T>;

  new_node->data = node_data;
  new_node->random = nullptr;
  new_node->left = nullptr;
  new_node->right = nullptr;

  return new_node;
}

template <typename T>
void print_inorder(Node<T>* node){
  if(node == nullptr)
    return;

  print_inorder(node->left);

  std::cout<<"["<<node->data<<" ";
  if(node->random == nullptr)
    std::cout<<"NULL], ";
  else
    std::cout<<node->random->data<<"], ";

  print_inorder(node->right);
}

template <typename T>
void copy_random_node(Node<T>* tree_node, Node<T>* clone_node){

  if(tree_node == nullptr)
    return;

  Node<T>* temp;
  temp = clone_node->random;
  clone_node->random = tree_node;
  tree_node->random = temp;
  copy_random_node(tree_node->left, clone_node->left);
  copy_random_node(tree_node->right, clone_node->right);

}

template <typename T>
void correct(Node<T>* tree_node, Node<T>* clone_node){
  if(clone_node == nullptr){
    if(tree_node->random != nullptr)
      if(tree_node->random->random != nullptr){
        Node<T>* temp;
        temp = clone_node->random->random;
        tree_node->random = clone_node->random->random;
        clone_node->random = temp;
      }
    else{
      tree_node->random = nullptr;
      clone_node->random= nullptr;
    }
    correct(tree_node->left, clone_node->left);
    correct(tree_node->right, clone_node->right);
  }

}

template <typename T>
Node<T>* clone(Node<T>* tree_node){
  if(tree_node == nullptr)
    return nullptr;

  Node<T> *new_node = new Node<T>;
  new_node->data = tree_node->data;
  new_node->left = clone(tree_node->left);
  new_node->right = clone(tree_node->right);
  // restore_tree_left_node(tree_node, clone_node);

  return new_node;
}

template <typename T>
Node<T>* clone_tree(Node<T>* head){
  Node<T>* clone_node = clone(head);
  copy_random_node(clone_node, head);
  correct(clone_node, head);
  return clone_node;
}

int main(){

  Node<int> *tree = new_node(10);
  Node<int> *n2 = new_node(6);
  Node<int> *n3 = new_node(12);
  Node<int> *n4 = new_node(5);
  Node<int> *n5 = new_node(8);
  Node<int> *n6 = new_node(11);
  Node<int> *n7 = new_node(13);
  Node<int> *n8 = new_node(7);
  Node<int> *n9 = new_node(9);

  tree->left = n2;
  tree->right = n3;
  tree->random = n2;
  n2->left = n4;
  n2->right = n5;
  n2->random = n8;
  n3->left = n6;
  n3->right = n7;
  n3->random = n5;
  n4->random = n9;
  n5->left = n8;
  n5->right = n9;
  n5->random = tree;
  n6->random = n9;
  n9->random = n8;

  std::cout<<"\nOriginal:"<<std::endl;
  print_inorder(tree);

  Node<int> *clone = clone_tree(tree);
  std::cout<<"\nClone:"<<std::endl;
  print_inorder(clone);

  return 0;
}
