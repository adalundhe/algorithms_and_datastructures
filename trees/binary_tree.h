#ifndef __BINARY_TREE_H_INCLUDES__
#define __BINARY_TREE_H_INCLUDES__

#include <algorithm>
#include <vector>
#include <iostream>
#include "../queues_and_stacks/stack.h"

template <typename T>
class BinaryTree{
  public:
    BinaryTree();
    BinaryTree(const T node_data);
    BinaryTree(const std::vector<T> node_data);
    void leftchild();
    void rightchild();
    void parent();
    unsigned leftchild(unsigned index);
    unsigned rightchild(unsigned index);
    unsigned parent(unsigned index);
    int node(const T query);
    T node_by_index(const unsigned index);
    bool hasleftchild() const;
    bool hasrightchild() const;
    bool hasparent() const;
    bool hasleftchild(unsigned index) const;
    bool hasrightchild(unsigned index) const;
    bool hasparent(unsigned index) const;
    virtual void insert(const T node_data);
    virtual void remove();
    virtual void remove(unsigned index);
    void clear();
    T at() const;
    T at(const unsigned index) const;
    int size() const;
    std::vector<T> level_order();
    std::vector<T> inorder();
    std::vector<T> preorder();
    std::vector<T> postorder();
    bool operator ==(BinaryTree<T> &other);
    bool operator !=(BinaryTree<T> &other);
  private:
    int current_node = 0;
    int tree_size = 0;
    std::vector<T> data;
    T get_left_child();
    T get_right_child();
    T get_left_child(unsigned index);
    T get_right_child(unsigned index);
};

template <typename T>
BinaryTree<T>::BinaryTree(){}

template <typename T>
BinaryTree<T>::BinaryTree(const T node_data){
  insert(node_data);
}

template <typename T>
BinaryTree<T>::BinaryTree(const std::vector<T> node_data){
  for(auto const &data_item : node_data)
    insert(data_item);
}

template <typename T>
void BinaryTree<T>::leftchild(){
  unsigned child_candidate = 2 * current_node + 1;

  if(child_candidate < tree_size)
    current_node = child_candidate;
}

template <typename T>
void BinaryTree<T>::rightchild(){
  unsigned child_candidate = 2 * current_node + 2;

  if(child_candidate < tree_size)
    current_node = child_candidate;
}

template <typename T>
void BinaryTree<T>::parent(){
  unsigned parent_candidate = (current_node - 1)/2;

  if(parent_candidate >= 0){
    current_node = parent_candidate;
  }
}

template <typename T>
unsigned BinaryTree<T>::leftchild(unsigned index){
  if(hasleftchild(index)) return 2 * index + 1;
  else return -1;
}

template <typename T>
unsigned BinaryTree<T>::rightchild(unsigned index){
  if(hasrightchild(index)) return 2 * index + 1;
  else return -1;
}

template <typename T>
unsigned BinaryTree<T>::parent(unsigned index){
  if(hasparent(index)) return (index - 1)/2;
  else return -1;
}

template <typename T>
int BinaryTree<T>::node(const T query){
  for(unsigned index=0; index<tree_size; index++)
    if(data.at(index) == query)
      return index;

  return -1;
}

template <typename T>
T BinaryTree<T>::node_by_index(const unsigned index){
  return data.at(index);
}

template <typename T>
bool BinaryTree<T>::hasleftchild() const{
  return (2 * current_node + 1) < tree_size;
}

template <typename T>
bool BinaryTree<T>::hasrightchild() const{
  return (2 * current_node + 2) < tree_size;
}

template <typename T>
bool BinaryTree<T>::hasleftchild(unsigned index) const{
  return (2 * index + 1) < tree_size;
}

template <typename T>
bool BinaryTree<T>::hasrightchild(unsigned index) const{
  return (2 * index + 2) < tree_size;
}

template <typename T>
bool BinaryTree<T>::hasparent() const{
  return (current_node - 1)/2;
}

template <typename T>
bool BinaryTree<T>::hasparent(unsigned index) const{
  return (index - 1)/2;
}

template <typename T>
T BinaryTree<T>::get_left_child(){
  return 2*current_node + 1;
}

template <typename T>
T BinaryTree<T>::get_right_child(){
  return 2*current_node + 2;
}

template <typename T>
T BinaryTree<T>::get_left_child(unsigned index){
  return 2*index + 1;
}

template <typename T>
T BinaryTree<T>::get_right_child(unsigned index){
  return 2*index + 2;
}

template <typename T>
void BinaryTree<T>::insert(const T node_data){
  data.push_back(node_data);
  tree_size++;
}

template <typename T>
T BinaryTree<T>::at() const{
  return data.at(current_node);
}

template <typename T>
T BinaryTree<T>::at(const unsigned index) const{
  if(index >= tree_size) return T();
  else return data.at(index);
}

template <typename T>
void BinaryTree<T>::remove(){
  data.pop_back();
  tree_size--;
}

template <typename T>
void BinaryTree<T>::remove(unsigned index){

  if(tree_size == 0) return;

  data.at(index) = data.at(tree_size-1);
  data.pop_back();
  tree_size--;

}

template <typename T>
int BinaryTree<T>::size() const{
  return tree_size;
}

template <typename T>
std::vector<T> BinaryTree<T>::level_order(){

  std::vector<T> traversal_values;

  for(unsigned i=0; i<tree_size; i++)
    traversal_values.push_back(i);

  return traversal_values;
}

template <typename T>
std::vector<T> BinaryTree<T>::inorder(){

  current_node = 0;
  std::vector<T> traversal_values;
  Stack<T> traversal_stack(tree_size);
  while(true){
    while(current_node < tree_size){
      traversal_stack.push(current_node);
      current_node = get_left_child(current_node);
    }

    if(traversal_stack.isempty())
      break;

    current_node = traversal_stack.pop();
    traversal_values.push_back(current_node);
    current_node = get_right_child(current_node);
  }

  current_node = 0;

  return traversal_values;
}

template <typename T>
std::vector<T> BinaryTree<T>::preorder(){

  current_node = 0;
  std::vector<T> traversal_values;
  Stack<T> traversal_stack(tree_size);

  std::cout<<"\nPrinting Tree via Preorder Traversal:\n"<<std::endl;

  while(!traversal_stack.isempty() || current_node < tree_size){


    if(current_node < tree_size){
      traversal_values.push_back(current_node);
      traversal_stack.push(current_node);
      current_node = get_left_child(current_node);
    }
    else{
      unsigned node = traversal_stack.pop();
      current_node = get_right_child(node);
    }
  }

  return traversal_values;

}

template <typename T>
std::vector<T> BinaryTree<T>::postorder(){

  current_node = 0;
  std::vector<T> traversal_values;
  Stack<T> traversal_stack(tree_size);
  traversal_stack.push(current_node);
  std::cout<<"\nPrinting Tree via Postorder Traversal:\n"<<std::endl;

  while(!traversal_stack.isempty()){

    current_node = traversal_stack.pop();
    traversal_values.push_back(current_node);

    if(get_left_child(current_node) < tree_size)
      traversal_stack.push(get_left_child(current_node));

    if(get_right_child(current_node) < tree_size)
      traversal_stack.push(get_right_child(current_node));

  }

  std::reverse(std::begin(traversal_values), std::end(traversal_values));

  return traversal_values;

}

template <typename T>
void BinaryTree<T>::clear(){
  data.clear();
  tree_size = 0;
}

template <typename T>
bool BinaryTree<T>::operator == (BinaryTree<T> &other){

  if(tree_size != other.size()) return false;

  unsigned size = tree_size;

  std::vector<int> nodes_of_current = inorder();
  std::vector<int> node_of_other = other.inorder();

  unsigned selected_node = 0;

  while(at(selected_node) == other.at(selected_node) && selected_node < size)
    selected_node++;

  if(selected_node == size-1) return false;
  else return true;

}

template <typename T>
bool BinaryTree<T>::operator != (BinaryTree<T> &other){

  if(tree_size != other.size()) return true;

  unsigned size = tree_size;

  std::vector<int> nodes_of_current = inorder();
  std::vector<int> node_of_other = other.inorder();

  unsigned selected_node = 0;

  while(at(selected_node) == other.at(selected_node) && selected_node < size)
    selected_node++;

  if(selected_node == size-1) return true;
  else return false;

}

#endif
