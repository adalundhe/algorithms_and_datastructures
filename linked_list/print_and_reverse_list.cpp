#include "linked_list.h"
#include <iostream>
#include <vector>

int main(){
  LinkedList<int> linked_list(1);

  std::vector<int> data = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  linked_list.append(data);

  while(!linked_list.end()){
    std::cout<<"ITEM AT:"<<linked_list.position()<<" IS: "<<linked_list.data()<<std::endl;
    linked_list.advance();
  }
  linked_list.reset();

  int stop = (linked_list.length()/2%2 == 0) ? linked_list.length()/2 : linked_list.length()/2 + 1;
  int current = linked_list.position();
  int tail = linked_list.length() - 1;

  while(current < stop){
    linked_list.swap(current, tail);
    current++;
    tail--;

  }
  linked_list.reset();

  while(!linked_list.end()){
    std::cout<<"PITEM AT:"<<linked_list.position()<<" IS: "<<linked_list.data()<<std::endl;
    linked_list.advance();
  }
  linked_list.reset();

  linked_list.clear();

  return 0;
}
