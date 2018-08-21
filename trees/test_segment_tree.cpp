#include "segment_tree.h"
#include <vector>
#include <iostream>

int main(){

  std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  SegmentTree<int> segment_tree(a);

  std::cout<<segment_tree.query(1, 3)<<std::endl;

  segment_tree.update(2, 1);

  std::cout<<segment_tree.query(1, 3)<<std::endl;

  return 0;
}
