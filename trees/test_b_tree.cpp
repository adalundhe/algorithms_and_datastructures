#include "b_tree.h"
#include <iostream>

int main(){

  BTree<int> tree(3);
  tree.insert(10);
  tree.insert(20);
  tree.insert(5);
  tree.insert(6);
  tree.insert(12);
  tree.insert(30);
  tree.insert(7);
  tree.insert(17);

  std::cout<<"Traversal of tree is: ";
  tree.traverse();
  std::cout<<std::endl;

  int query = 6;
  std::cout<<((tree.search(query) != nullptr) ? "Present" : "Not Present")<<std::endl;

  query = 15;
  std::cout<<((tree.search(query) != nullptr) ? "Present" : "Not Present")<<std::endl;

  return 0;
}
