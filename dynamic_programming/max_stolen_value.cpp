#include <vector>
#include <iostream>
#include <algorithm>

int find_maximum_value(const std::vector<int> houses, int N){

  if(N == 0) return 0;
  if(N == 1) return houses.at(0);
  if(N == 2) return std::max(houses.at(0), houses.at(1));

  int table[N];
  table[0] = houses.at(0);
  table[1] = std::max(houses.at(0), houses.at(1));

  for(unsigned i=2; i<N; i++){
    table[i] = std::max(houses.at(i) + table[i-2], table[i-1]);
  }

  return table[N-1];
}

int main(){
  std::vector<int> houses = {5, 3, 4, 11, 2};
  int N = houses.size();

  unsigned max_return = find_maximum_value(houses, N);

  std::cout<<"Maximum value of loot is: "<<max_return<<std::endl;

  return 0;
}
