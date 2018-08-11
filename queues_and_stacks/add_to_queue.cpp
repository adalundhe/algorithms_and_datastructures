#include "queue.h"
#include <vector>
#include <iostream>

int main(){
  std::vector<int> data = {1, 2, 3, 4, 5};

  Queue<int> queue(data);
  int size = queue.length();

  int data = queue.peep();

  std::cout<<data<<std::endl;

  for(int i=0; i<size; i++){

    int data = queue.dequeue();

    std::cout<<data<<std::endl;
  }

}
