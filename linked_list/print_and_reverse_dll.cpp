#include "doubly_linked_list.h"
#include <iostream>
#include <vector>


int main(){
  std::vector<int> data = {1, 2, 3, 4, 5};
  std::vector<int> data_two = {11, 12, 13, 14, 15};
  std::vector<int> data_three = {6, 7, 8, 9 , 10};

  DoublyLinkedList<int> dll(data);
  dll.insert(data_two, 4);

  int insert_index = dll.index(11);

  dll.insert(data_three, insert_index);

  while(!dll.isend()){
    std::cout<<"GOT: "<<dll.data()<<std::endl;
    dll.advance();
  }

  dll.reset();

  dll.reverse();
  dll.reset();

  while(!dll.isend()){
    std::cout<<"GOT: "<<dll.data()<<" AT: "<<dll.position()<<std::endl;
    dll.advance();
  }
  dll.reset();

  dll.toend();


  while(!dll.isend()){
    std::cout<<"REVERSE: "<<dll.data()<<" AT: "<<dll.position()<<std::endl;
    dll.back();
  }


  return 0;
}
