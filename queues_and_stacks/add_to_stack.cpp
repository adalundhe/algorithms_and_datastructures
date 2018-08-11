#include "stack.h"
#include <vector>
#include <iostream>

int main(){
  std::vector<int> data = {3, 5, 2, 1, 1, -1};

  Stack<int> stack(data, 6);
  int size = stack.length();

  for(int i=0; i<size; i++){

    int data = stack.pop();

    std::cout<<data<<std::endl;
  }

}
