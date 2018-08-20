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
    void insert_non_full_node(T data);
    void split_child(int index, BTreeNode<T> *node);
    T *keys;
    BTreeNode<T> **children;
    int minimum_degree;
    int current_key_count;
    bool is_leaf;
};

template <typename T>
class BTree{
  public:
    BTree(int initial_min_degree);
    void traverse();
    BTreeNode<T>* search(T query);
    void insert(T data);
  private:
    BTreeNode<T> *root;
    int minimum_degree;
};

template <typename T>
BTreeNode<T>::BTreeNode(int initial_min_degree, bool node_is_leaf){

  minimum_degree = initial_min_degree;
  is_leaf = node_is_leaf;

  keys = (T*)malloc(sizeof(T) * (2*minimum_degree - 1));
  children = (BTreeNode**)malloc(sizeof(BTreeNode*) * (2 * minimum_degree));

  current_key_count = 0;

}

template <typename T>
void BTreeNode<T>::insert_non_full_node(T data){

  int i = current_key_count-1;

  if (is_leaf == true){
    while(i >= 0 && keys[i] > data){
      keys[i+1] = keys[i];
      i--;
    }
    keys[i+1] = data;
    current_key_count++;
  }
  else{
    while(i >= 0 && keys[i] > data){
      i--;
    }
    if(children[i+1]->current_key_count == 2*minimum_degree-1){
      split_child(i+1, children[i+1]);
      if(keys[i+1] < data)
        i++;
    }
    children[i+1]->insert_non_full_node(data);
  }

}

template <typename T>
void BTreeNode<T>::split_child(int index, BTreeNode *node){

  BTreeNode *new_node = new BTreeNode(node->minimum_degree, node->is_leaf);
  new_node->current_key_count = minimum_degree-1;

  for(unsigned j=0; j<minimum_degree-1; ++j)
    new_node->keys[j] = node->keys[j+minimum_degree];

  if(node->is_leaf == false)
    for(unsigned j=0; j<minimum_degree; ++j)
      new_node->children[j] = node->children[j+minimum_degree];

  node->current_key_count = minimum_degree-1;

  for(int j=current_key_count; j >= index+1; --j)
    children[j+1] = children[j];

  children[index+1] = new_node;

  for(int j=current_key_count-1; j>=index; --j)
    keys[j+1] = keys[j];

  keys[index] = node->keys[minimum_degree-1];

  current_key_count++;

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

  int i=0;

  while(i < current_key_count && query > keys[i])
    i++;

  if(keys[i] == query)
    return this;

  if(is_leaf)
    return nullptr;

  return children[i]->search(query);

}

template <typename T>
BTree<T>::BTree(int initial_min_degree){
  root = nullptr;
  minimum_degree = initial_min_degree;
}

template <typename T>
void BTree<T>::traverse(){

  if(root != nullptr)
    root->traverse();

}

template <typename T>
BTreeNode<T>* BTree<T>::search(T query){
  if(root == nullptr)
    return nullptr;

  return root->search(query);
}

template <typename T>
void BTree<T>::insert(T data){

  if(root == nullptr){
    root = new BTreeNode<T>(minimum_degree, true);
    root->keys[0] = data;
    root->current_key_count = 1;
  }
  else{
    if(root->current_key_count == 2*minimum_degree-1){
      BTreeNode<T> *new_node = new BTreeNode<T>(minimum_degree, false);
      new_node->children[0] = root;
      new_node->split_child(0, root);

      int i=0;
      if(new_node->keys[0] < data)
        i++;
      new_node->children[i]->insert_non_full_node(data);

      root = new_node;
    }
    else{
      root->insert_non_full_node(data);
    }
  }

}

#endif
