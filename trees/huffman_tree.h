#ifndef __HUFFMAN_TREE_H_INCLUDES__
#define __HUFFMAN_TREE_H_INCLUDES__

#include "min_heap.h"
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class HuffmanTree : public MinHeap<T>{
  public:

};

template <typename T>
HuffmanTree<T>::HuffmanTree():MinHeap<T>(){}

template <typename T>
HuffmanTree<T>::HuffmanTree(T node_data){
  MinHeap<T>::insert(node_data);
}


#endif
