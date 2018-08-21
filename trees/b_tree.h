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
    int find_key(T query);
    void remove(T query);
    void remove_from_leaf(T idx);
    void remove_from_nonleaf(T idx);
    T get_predecessor(T idx);
    T get_successor(T idx);
    void fill(T idx);
    void borrow_from_prev(T idx);
    void borrow_from_next(T idx);
    void merge(T idx);
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
    void remove(T query);
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
int BTreeNode<T>::find_key(T query){

  int idx = 0;

  while(idx<current_key_count && keys[idx] < query)
    ++idx;
  return idx;
}

template <typename T>
void BTreeNode<T>::remove(T query){

  int idx = find_key(query);

  if(idx < current_key_count && keys[idx] == query){
    if(is_leaf)
      remove_from_leaf(idx);
    else
      remove_from_nonleaf(idx);
  }
  else{
    if(is_leaf)
      return;
    bool removal_flag = (idx==current_key_count) ? true: false;

    if(children[idx]->current_key_count < minimum_degree)
      fill(idx);
    if(removal_flag && idx > current_key_count)
      children[idx-1]->remove(query);
    else
      children[idx]->remove(query);
  }

  return;
}

template <typename T>
void BTreeNode<T>::remove_from_leaf(T idx){
  for(int i=idx+1; i<current_key_count; ++i)
    keys[i-1] = keys[i];
  current_key_count--;
  return;
}

template <typename T>
void BTreeNode<T>::remove_from_nonleaf(T idx){

  T selected_key = keys[idx];

  if(children[idx]->current_key_count >= minimum_degree){
    T predecessor_idx = get_predecessor(idx);
    keys[idx] = predecessor_idx;
    children[idx]->remove(predecessor_idx);
  }
  else if(children[idx+1]->current_key_count >= minimum_degree){
    T successor_idx = get_successor(idx);
    keys[idx] = successor_idx;
    children[idx+1]->remove(successor_idx);
  }
  else{
    merge(idx);
    children[idx]->remove(selected_key);
  }
  return;
}

template <typename T>
T BTreeNode<T>::get_predecessor(T idx){
  BTreeNode<T> *current = children[idx];
  while(current->is_leaf == false)
    current = current->children[current->current_key_count];

  return current->keys[current->current_key_count-1];
}

template <typename T>
T BTreeNode<T>::get_successor(T idx){
  BTreeNode<T> *current = children[idx+1];
  while(current->is_leaf == false)
    current = current->children[0];
  return current->keys[0];
}

template <typename T>
void BTreeNode<T>::fill(T idx){
  if(idx != 0 && children[idx-1]->current_key_count >= minimum_degree)
    borrow_from_prev(idx);
  else if(idx != current_key_count && children[idx+1]->current_key_count >= minimum_degree)
    borrow_from_next(idx);
  else{
    if(idx != current_key_count)
      merge(idx);
    else
      merge(idx-1);
  }
  return;
}

template <typename T>
void BTreeNode<T>::borrow_from_prev(T idx){
  BTreeNode<T> *child = children[idx];
  BTreeNode<T> *sibling = children[idx-1];

  for(int i=child->current_key_count-1; i>=0; --i)
    child->keys[i+1] = child->keys[i];

  child->keys[0] = keys[idx-1];

  if(child->is_leaf == false)
    child->children[0] = sibling->children[sibling->current_key_count];

  keys[idx-1] = sibling->keys[sibling->current_key_count-1];

  child->current_key_count++;
  sibling->current_key_count--;

  return;
}

template <typename T>
void BTreeNode<T>::borrow_from_next(T idx){

  BTreeNode<T> *child = children[idx];
  BTreeNode<T> *sibling = children[idx+1];

  child->keys[child->current_key_count] = keys[idx];

  if(child->is_leaf == false)
    child->children[child->current_key_count + 1] = sibling->children[0];

  keys[idx] = sibling->keys[0];

  for(int i=1; i<sibling->current_key_count; ++i)
    sibling->keys[i-1] = sibling->keys[i];

  if(sibling->is_leaf == false)
    for(int i=1; i<=sibling->current_key_count; ++i)
      sibling->children[i-1] = sibling->children[i];

  child->current_key_count++;
  sibling->current_key_count--;

  return;
}

template <typename T>
void BTreeNode<T>::merge(T idx){

  BTreeNode<T> *child = children[idx];
  BTreeNode<T> *sibling = children[idx+1];

  child->keys[minimum_degree-1] = keys[idx];

  for(unsigned i=0; i<sibling->current_key_count; ++i)
    child->keys[i+minimum_degree] = sibling->keys[i];

  if(child->is_leaf == false)
    for(unsigned i=0; i<=sibling->current_key_count; ++i)
      child->children[i+minimum_degree] = sibling->children[i];

  for(unsigned i=idx+1; i<current_key_count; ++i)
    keys[i-1] = keys[i];

  for(unsigned i=idx+2; i<=current_key_count; ++i)
    children[i-1] = children[i];

  child->current_key_count += sibling->current_key_count + 1;
  current_key_count--;

  delete(sibling);
  return;
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

template <typename T>
void BTree<T>::remove(T query){

  if(root == nullptr)
    return;

  root->remove(query);

  if(root->current_key_count == 0){
    BTreeNode<T> *temp = root;
    if(root->is_leaf)
      root = nullptr;
    else
      root = root->children[0];

    delete temp;
  }
  return;

}

#endif
