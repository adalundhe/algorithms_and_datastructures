#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

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
bool match_found(std::queue<std::pair<T, T>> *node_queue){

  int level_size = node_queue->size();
  int matches = 0;

  while(!node_queue->empty()){
    std::pair<T, T> node_pair_data = node_queue->back();
    node_queue->pop();

    if(node_pair_data.first == node_pair_data.second)
      matches++;
  }

  if(matches == level_size)
    return true;

  return false;

}

template <typename T>
bool check_isomorphism(Node<T> *root_one, Node<T> *root_two){

  std::queue<std::pair<T, T>> node_data_queue_one;
  std::queue<std::pair<T, T>> node_data_queue_two;
  std::queue<Node<T>*> node_queue_one;
  std::queue<Node<T>*> node_queue_two;

  node_data_queue_one.push(
    std::make_pair(root_one->data, root_two->data)
  );

  node_data_queue_two.push(
    std::make_pair(root_one->data, root_two->data)
  );

  node_queue_one.push(root_one);
  node_queue_two.push(root_two);

  while(!node_queue_one.empty() && ! node_queue_two.empty()){

    bool case_one_matched = match_found(&node_data_queue_one);
    bool case_two_matched = match_found(&node_data_queue_two);

    if(!case_one_matched && !case_two_matched)
      return false;

    int current_size_one = node_queue_one.size();
    int current_size_two = node_queue_two.size();


    while(current_size_one > 0 && current_size_two > 0){
        Node<T> * current_node_one = node_queue_one.front();
        node_queue_one.pop();
        Node<T> * current_node_two = node_queue_two.front();
        node_queue_two.pop();

        if(current_node_one->left && current_node_two->left){
          node_queue_one.push(current_node_one->left);
          node_queue_two.push(current_node_two->left);
        }
        if(current_node_one->right && current_node_two->right){
          node_queue_one.push(current_node_one->right);
          node_queue_two.push(current_node_two->right);
        }
        if(current_node_one->left && current_node_two->left)
          node_data_queue_one.push(
            std::make_pair(current_node_one->left->data, current_node_two->left->data)
          );
        if(current_node_one->right && current_node_two->right)
          node_data_queue_one.push(
            std::make_pair(current_node_one->right->data, current_node_two->right->data)
          );
        if(current_node_one->left && current_node_two->right)
          node_data_queue_two.push(
            std::make_pair(current_node_one->left->data, current_node_two->right->data)
          );
        if(current_node_one->right && current_node_two->left)
          node_data_queue_two.push(
            std::make_pair(current_node_one->right->data, current_node_two->left->data)
          );
        current_size_one--;
        current_size_two--;

    }


  }

  return true;
}

int main(){

  Node<int> *root = create_node(1);
  root->left = create_node(2);
  root->right = create_node(3);
  root->left->left = create_node(4);
  root->left->right = create_node(5);
  root->right->left = create_node(6);
  root->right->right = create_node(7);

  Node<int> *root_two = create_node(1);
  root_two->left = create_node(2);
  root_two->right = create_node(3);
  root_two->left->left = create_node(4);
  root_two->left->right = create_node(5);
  root_two->right->left = create_node(6);
  root_two->right->right = create_node(7);

  bool result = check_isomorphism(root, root_two);

  std::cout<<"Tree one is "<<(result ? "isomorphic" : "not isomorphic")<<" to tree two."<<std::endl;

  return 0;
}
