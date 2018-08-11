#include "binary_tree.h"
#include "min_heap.h"
#include <vector>
#include <iostream>

int main(){

  const std::vector<int> data = {0, 6, 3, 2, 5, 4, 1};

  MinHeap<int> min_heap(data);
  // min_heap.heapify();

  std::vector<int> result = min_heap.level_order();

  for(auto const &data_item : result)
    std::cout<<min_heap.at(data_item)<<std::endl;

  MinHeap<int> min_heap_two(data);
  min_heap_two.heapify();

  std::cout<<"\nTWO: \n"<<std::endl;
  for(auto const &data_item : result)
    std::cout<<min_heap.at(data_item)<<std::endl;

  std::cout<<"\nMinimum Is: "<<min_heap.get_minimum()<<std::endl;

  min_heap.delete_minimum();

  std::cout<<"\nMinimum Is: "<<min_heap.get_minimum()<<std::endl;

  min_heap.delete_minimum();

  std::cout<<"\nMinimum Is: "<<min_heap.get_minimum()<<std::endl;

  return 0;
}
