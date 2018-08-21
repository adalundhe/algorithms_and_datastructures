#include "fenwick_tree.h"
#include <vector>
#include <iostream>

int main(){

  std::vector<int> freq = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
  FenwickTree<int> fenwick_tree(freq);

  std::cout<<"Sum of elements in arr[0..5] is "<< fenwick_tree.query(5)<<std::endl;

  fenwick_tree.update(3, 6);
  std::cout<<"\nSum of elements in arr[0..5] after update is "<<fenwick_tree.query(5)<<std::endl;

  return 0;
}
