#include <iostream>
#include <time.h>

int get_max_rotation_sum(int array[], int N){
  int arraySum = 0;
  int maximumSum = 0;
  int currentSum = 0;

  for(unsigned i=0; i<N; i++){
      arraySum += array[i];
      currentSum += i * array[i];
  }

  maximumSum = currentSum;

  for(unsigned j=1; j<N; j++){
    currentSum += arraySum - N*array[N-j];
    if(currentSum > maximumSum){
      maximumSum = currentSum;
    }
  }

  return maximumSum;
}

int main(){

  srand(time(NULL));

  int N = 10:

  int array[N];

  for(unsigned i=0; i<N; i++) array[i] = rand()%(N*N) + 1;

  return 0;
}
