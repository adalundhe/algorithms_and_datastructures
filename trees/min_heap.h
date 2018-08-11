#ifndef __MIN_HEAP_H_INCLUDES__
#define __MIN_HEAP_H_INCLUDES__

#include "binary_tree.h"
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class MinHeap : public BinaryTree<T>{
  public:
    MinHeap();
    MinHeap(T node_data);
    MinHeap(std::vector<T> node_data);
    void insert(const T node_data);
    void heapify();
    T get_minimum();
    void delete_minimum();
  private:
    void bubble_down(std::vector<T> *copy_tree, unsigned index);
    void bubble_up(std::vector<T> *copy_tree, unsigned index);
    std::vector<T> create_copy();
    void insert_copy(std::vector<T> copy_tree);
};

template <typename T>
MinHeap<T>::MinHeap():BinaryTree<T>(){}

template <typename T>
MinHeap<T>::MinHeap(T node_data){
  insert(node_data);
}

template <typename T>
MinHeap<T>::MinHeap(std::vector<T> node_data){
  for(auto const &data : node_data) insert(data);
}

template <typename T>
void MinHeap<T>::insert(const T node_data){

    BinaryTree<T>::insert(node_data);

    std::vector<T> copy_tree = create_copy();
    unsigned index = copy_tree.size()-1;

    bubble_up(&copy_tree, index);
    insert_copy(copy_tree);

}

template <typename T>
void MinHeap<T>::heapify(){

  std::vector<T> copy_tree = create_copy();

  unsigned length = copy_tree.size()-1;
  for(int index=length; index>= 0; --index){
    bubble_down(&copy_tree, index);
  }

  insert_copy(copy_tree);

}

template <typename T>
void MinHeap<T>::bubble_down(std::vector<T> *copy_tree, unsigned index){

  unsigned length = copy_tree->size()-1;
  unsigned left_child_index = 2 * index + 1;
  unsigned right_child_index = 2 * index +2;

  if(left_child_index > length)
    return;

  int minimum_index = index;

  if(copy_tree->at(index) > copy_tree->at(left_child_index))
    minimum_index = left_child_index;

  if((right_child_index < length) && (copy_tree->at(minimum_index) > copy_tree->at(right_child_index)))
    minimum_index = right_child_index;

  if(minimum_index != index){
    unsigned temp = copy_tree->at(index);
    copy_tree->at(index) = copy_tree->at(minimum_index);
    copy_tree->at(minimum_index) = temp;
    this->bubble_down(copy_tree, minimum_index);
  }
}

template <typename T>
void MinHeap<T>::bubble_up(std::vector<T> *copy_tree, unsigned index){
  if(index == 0)
    return;

  unsigned parent_index = (index-1)/2;

  if(copy_tree->at(parent_index) > copy_tree->at(index)){
    unsigned temp = copy_tree->at(parent_index);
    copy_tree->at(parent_index) = copy_tree->at(index);
    copy_tree->at(index) = temp;
    this->bubble_up(copy_tree, index);
  }
}

template <typename T>
std::vector<T> MinHeap<T>::create_copy(){

  unsigned size = BinaryTree<T>::size();
  std::vector<T> copy_tree;

  for(unsigned i=0; i<size; i++){
    T data_item = BinaryTree<T>::at(i);
    copy_tree.push_back(data_item);
  }

  BinaryTree<T>::clear();

  return copy_tree;

}

template <typename T>
void MinHeap<T>::insert_copy(std::vector<T> copy_tree){
  for(auto const &data_item : copy_tree)
    BinaryTree<T>::insert(data_item);
}

template <typename T>
T MinHeap<T>::get_minimum(){
  return BinaryTree<T>::node_by_index(0);
}

template <typename T>
void MinHeap<T>::delete_minimum(){
  BinaryTree<T>::remove(0);

  std::vector<T> copy_tree;

  heapify();
}

#endif
