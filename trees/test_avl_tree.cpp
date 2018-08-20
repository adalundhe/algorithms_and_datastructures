#include "avl_tree.h"
#include <iostream>

int main(){

  AVLTree<int> avl_tree;
  avl_tree.insert(10);
  avl_tree.insert(20);
  avl_tree.insert(30);
  avl_tree.insert(40);
  avl_tree.insert(50);
  avl_tree.insert(25);
  avl_tree.print();

  std::cout<<std::endl;

  avl_tree.remove(50);
  avl_tree.print();

  int data = avl_tree.find(30);

  std::cout<<std::endl<<data<<std::endl;

  return 0;
}
