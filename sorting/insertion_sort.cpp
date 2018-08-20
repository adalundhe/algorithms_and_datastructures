#include <iostream>

void insertion_sort(int A[], int N){

  int i=0;
  int key=0;
  int j=0;

  for(i=1; i<N; ++i){

    key = A[i];
    j = i-1;

    while(j >= 0 && A[j] > key){
      A[j+1] = A[j];
      j = j-1;
    }

    A[j+1] = key;

  }


}

int main(){

  int A[] = {4, 5, 2, 7, 1};
  int N = sizeof(A)/sizeof(A[0]);

  insertion_sort(A, N);

  for(unsigned i=0; i<N; ++i)
    std::cout<<A[i]<<std::endl;

  return 0;
}
