#include <iostream>
#include <queue>

template <typename T>
struct Node{
  T data;
  Node *left, *right;
};

template <typename T>
Node<T>* create_node(T node_data){
  Node<T> *node = new Node<T>;
  node->data = node_data;
  node->left = nullptr;
  node->right = nullptr;

  return node;

}

template <typename T>
int sum_all_nodes(Node<T> *root){

  int sum = 0;

  if(root == nullptr)
    return 0;

  std::queue<Node<T>*> node_queue;
  node_queue.push(root);

  while(!node_queue.empty()){
      Node<T>* current_node = node_queue.front();
      sum += current_node->data;
      node_queue.pop();

      if(current_node->left)
        node_queue.push(current_node->left);
      if(current_node->right)
        node_queue.push(current_node->right);
  }

  return sum;

}

int main(){

  Node<int> *root = create_node(1);
  root->left = create_node(2);
  root->right = create_node(3);
  root->left->left = create_node(4);
  root->left->right = create_node(5);
  root->right->left = create_node(6);
  root->right->right = create_node(7);

  int result = sum_all_nodes(root);

  std::cout<<"Sum of all nodes in tree is: "<<result<<std::endl;

  return 0;
}
