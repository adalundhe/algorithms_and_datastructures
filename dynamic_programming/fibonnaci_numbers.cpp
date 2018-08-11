#include <iostream>

int fibonnaci_sum(int n){
  int table[n+2];

  table[0] = 0;
  table[1] = 1;

  for(unsigned i=2; i<=n; ++i)
    table[i] = table[i-1] + table[i-2];

  return table[n];
}

int main(){
  int n = 9;
  int result = fibonnaci_sum(n);

  std::cout<<"Got: "<<result<<std::endl;

  return 0;

}
