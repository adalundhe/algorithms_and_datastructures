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
Node<T>* find_node(Node<T> *root, T target){

  if(root == nullptr)
    return nullptr;

  std::queue<Node<T>*> node_queue;
  node_queue.push(root);

  while(!node_queue.empty()){
      Node<T>* current_node = node_queue.front();
      node_queue.pop();

      if(current_node->data == target)
        return current_node;

      if(current_node->left)
        node_queue.push(current_node->left);
      if(current_node->right)
        node_queue.push(current_node->right);
  }

  return nullptr;

}

int main(){

  Node<int> *root = create_node(1);
  root->left = create_node(2);
  root->right = create_node(3);
  root->left->left = create_node(4);
  root->left->right = create_node(5);
  root->right->left = create_node(6);
  root->right->right = create_node(7);

  Node<int> *result = find_node(root, 5);
  if(result == nullptr)
    std::cout<<"Query not found."<<std::endl;
  else
    std::cout<<"Query "<<result->data<<" found at node with address: "<<result<<"."<<std::endl;

  return 0;
}
