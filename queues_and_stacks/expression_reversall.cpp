#include "stack.h"
#include <string>
#include <iostream>

int fix_expression(const std::string expression, Stack<char> * __restrict__ stack){
  const unsigned expression_length = expression.length();

  if(expression_length%2 != 0)
    return 0;

  for(auto const &c : expression){
    if(c == '}' && !stack->isempty()){
      if(stack->peep() == '{')
        stack->pop();
      else
        stack->push(c);
    }
    else{
      stack->push(c);
    }
  }

  return stack->length();
}

int count_reversals(Stack<char> * __restrict__ stack, const unsigned result_size){
  int reversal_count = 0;

  while(!stack->isempty() && stack->peep() == '{'){
    stack->pop();
    reversal_count++;
  }

  return (result_size/2 + reversal_count%2);

}

int main(){

  const std::string expression = "}{{{";
  const unsigned expression_length = expression.length();
  unsigned result_size = 0;
  unsigned reversals = 0;

  Stack<char> stack(expression_length);

  result_size = fix_expression(expression, &stack);
  reversals = count_reversals(&stack, result_size);

  std::cout<<"This expression requires: "<<reversals<<" reversals."<<std::endl;


  return 0;
}
