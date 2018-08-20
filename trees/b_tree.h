#ifndef __B_TREE_H_INCLUDES__
#define __B_TREE_H_INCLUDES__
#include <stdlib.h>
#include <iostream>

template <typename T>
class BTreeNode{
  public:
    BTreeNode(int initial_min_degree, bool node_is_leaf);
    virtual void traverse();
    virtual BTreeNode<T>* search(T query);
    friend class BTree;
  private:
    T *keys;
    BTreeNode **children;
    int minimum_degree;
    int current_key_count;
    bool is_leaf;
};

template <typename T>
class BTree{
  public:
    BTree(int initial_degree);
    void traverse();
    BTreeNode<T>* search(T query);
  private:
    BTreeNode<T> *root;
    int minimum_degree;
};

template <typename T>
BTreeNode<T>::BTreeNode(int initial_min_degree, bool node_is_leaf){

  minimum_degree = initial_min_degree;
  is_leaf = node_is_leaf;

  keys = (T*)malloc(sizeof(T) * (2*minimum_degree - 1));
  children = (BTreeNode*)malloc(sizeof(BTreeNode*) * (2 * minimum_degree));

  current_key_count = 0;

}

template <typename T>
void BTreeNode<T>::traverse(){

  unsigned i=0;

  for(i=0; i<current_key_count; ++i){
    if(is_leaf == false)
      children[i]->traverse();
    std::cout<<" "<<keys[i];
  }

  if(is_leaf == false)
    children[i]->traverse();

}

template <typename T>
BTreeNode<T>* BTreeNode<T>::search(T query){

  unsigned i=0;

  while(i < current_key_count && query > keys[i])
    i++;

  if(keys[i] == query)
    return this;

  if(is_leaf)
    return nullptr;

  return children[i]->search(query);

}

#endif
