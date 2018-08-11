#include <vector>
#include <iostream>
#include <numeric>
#include <bits/stdc++.h>

void find_subsets(std::vector<int> data, int N, std::vector<int> *set_a, std::vector<int> *set_b){

  int i, current_sum;

  int sum = std::accumulate(data.begin(), data.end(), 0);

  if(sum & 1)
    return;

  int k = sum >> 1;

  bool table[N + 1][k + 1];

  for(i=1; i<= k; i++)
    table[0][i] = false;

  for(i=0; i<= N; i++)
    table[i][0] = true;

  for(i=1; i<= N; i++){
    for(current_sum = 1; current_sum<=k; current_sum++){
      table[i][current_sum] = table[i - 1][current_sum];
      if(data[i - 1] <= current_sum)
        table[i][current_sum] = table[i][current_sum] | table[i - 1][current_sum - data[i - 1]];
    }
  }

  i=N;
  current_sum=k;

  while(i > 0 && current_sum >= 0){
    if(table[i - 1][current_sum]){
      i--;
      set_b->push_back(data[i]);
    }
    else if(table[i-1][current_sum - data[i - 1]]){
      i--;
      current_sum -= data[i];
      set_a->push_back(data[i]);
    }
  }

  return;
}

int main(){

  std::vector<int> data = {5, 5, 1, 11, 2, 3, 1};
  std::vector<int> set_a;
  std::vector<int> set_b;
  bool result = false;

  int N = data.size();

  find_subsets(data, N, &set_a, &set_b);

  std::cout<<"SET 1: "<<std::endl;
  for(auto const &number: set_a)
    std::cout<<number<<std::endl;

  std::cout<<"SET 2:"<<std::endl;
  for(auto const  &number : set_b)
    std::cout<<number<<std::endl;

  return 0;
}
