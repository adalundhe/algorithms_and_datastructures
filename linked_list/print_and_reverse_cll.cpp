#include "circular_linked_list.h"
#include <iostream>
#include <vector>

int main(){

  std::vector<int> data = {1, 2, 3, 4, 5};

  CircularLinkedList<int> cll(data);

  while(!cll.isend()){
    std::cout<<cll.position()<<" "<<cll.data()<<std::endl;
    cll.advance();
  }
  cll.advance();

  std::cout<<cll.position()<<" "<<cll.data()<<std::endl;

  return 0;
}
