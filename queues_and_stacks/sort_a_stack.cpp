#include "stack.h"
#include <iostream>
#include <vector>

void sort_stack(Stack<int> * __restrict__ stack){
  unsigned length = stack->length();
  Stack<int> temp_stack(length);

  while(!stack->isempty()){
    int data_item = stack->pop();

    while(!temp_stack.isempty() && temp_stack.peep() > data_item)
      stack->push(temp_stack.pop());

    temp_stack.push(data_item);


  }

  while(!temp_stack.isempty())
    stack->push(temp_stack.pop());

}

int main(){
  std::vector<int> data = {34, 3, 31, 98, 92, 23};
  unsigned length = data.size();

  Stack<int> stack(data, length);

  sort_stack(&stack);

  std::cout<<"RESULT: "<<std::endl;
  while(!stack.isempty())
    std::cout<<stack.pop()<<std::endl;

}
