#include <iostream>
#include <vector>
#include "stack.h"

int find_span(std::vector<int> stock_prices, std::vector<int> * __restrict__ spans, Stack<int> stack){

  unsigned number_of_stocks = stock_prices.size();
  stack.push(0);
  spans->at(0) = 1;

  for(unsigned i=1; i<number_of_stocks; i++){
    while(!stack.isempty() && stock_prices[stack.peep()] <= stock_prices[i])
      stack.pop();

    spans->at(i) = stack.isempty() ? (i + 1) : (i - stack.peep());

    stack.push(i);
  }


}

int main(){

  std::vector<int> stock_prices = {10, 4, 5, 90, 120, 80};
  unsigned number_of_stocks = stock_prices.size();
  std::vector<int> spans(number_of_stocks, 0);

  Stack<int> stack(number_of_stocks);

  find_span(stock_prices, &spans, stack);

  std::cout<<"SPANS: "<<std::endl;
  for(auto const &span : spans){
    std::cout<<span<<std::endl;
  }


  return 0;
}
