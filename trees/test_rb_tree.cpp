#include "red_black_tree.h"

int main(){

  RedBlackTree<int> rb_tree;

  rb_tree.insert(7);
  rb_tree.insert(6);
  rb_tree.insert(5);
  rb_tree.insert(4);
  rb_tree.insert(3);
  rb_tree.insert(2);
  rb_tree.insert(1);

  rb_tree.print();

  return 0;
}
