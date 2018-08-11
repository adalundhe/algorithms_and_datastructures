#include <algorithm>
#include <iostream>

long long int permutation_coefficient(int n, int k){

  long long int f_n = 1;
  long long int f_k = 0;

  long long int factorial_table[n+1];

  for(unsigned i=1; i<=n; ++i){
    f_n *= i;

    if(i == n-k)
      f_k = f_n;

  }

  return f_n/f_k;

}

int main(){

  int n = 10;
  int k=2;

  long long int result = permutation_coefficient(n, k);

  std::cout<<"Got: "<<result<<std::endl;


  return 0;
}
