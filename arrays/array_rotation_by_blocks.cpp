#include <stdlib.h>
#include <string.h>
#include <iostream>

void swap(int array[], int start_a, int start_b, int k){
  int i, temp;

  for(i=0; i<k; i++){
    temp = array[start_a + i];
    array[start_a + i] = array[start_b + i];
    array[start_b + i] = temp;
  }
}

void rotate(int *array, int N, int k){
  int i, j;
  k = k%N;

  if(k==0 || k==N){
      return;
  }
  i = k;
  j = N -k;

  while(i != j){
    if(i < j){
      swap(array, k-i, k+j-i, i);
      j -= i;
    }
    else{
      swap(array, k-i, k, j);
      i -= j;
    }
  }

  swap(array, k-i, k, i);
}

int main(){

  int N = 10;
  int k = 19;

  int *numbers = (int*)malloc(sizeof(int) * N);

  for(int i=0; i<N; i++) numbers[i] = i+1;

  rotate(numbers, N, k);

  for(int i=0; i<N; i++){
    std::cout<<numbers[i]<<std::endl;
  }

  return 0;
}
