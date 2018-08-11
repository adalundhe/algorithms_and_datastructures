#include <iostream>
#include <algorithm>

void swap(long long int * __restrict__ a, long long int *__restrict__ b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

long long int* cache_oblivious_transpose(long long int *A, int M, int N){

  unsigned BLOCK_SIZE = 128;
  long long int* result = (long long int*)malloc(sizeof(long long int) * M * N);

  for(unsigned i=0; i<M; i+=BLOCK_SIZE)
    for(unsigned j=0; j<N; j+=BLOCK_SIZE)
      for(unsigned k=i; k<i + BLOCK_SIZE; ++k)
        for(unsigned l=j; l< j + BLOCK_SIZE; ++l)
          result[k * N + l] = A[l * N + k];


  free(A);
  return result;

}


long long int* reverse_columns(long long int *A, int M, int N){

  int BLOCK_SIZE = 64;
  int column_flip_size = (N%2 == 0) ? N/2 : (N/2) + 1;

  for(unsigned i=0; i<M; i+=BLOCK_SIZE)
    for(unsigned j=0, k=N-1; j<column_flip_size; j+=BLOCK_SIZE, k-=BLOCK_SIZE)
      for(unsigned l=i; l< i + BLOCK_SIZE; ++l)
        for(unsigned m=j, n=k; m < BLOCK_SIZE; ++m, --n)
            swap(&A[m * N + l], &A[n * N + l]);


  return A;
}

int main(){

  int M = 12288;
  int N = 12288;
  long long int *A = (long long int*)malloc(sizeof(long long int) * M * N);

  for(unsigned i=1; i<=(M * N); ++i)
    A[i] = i;


  long long int* result = cache_oblivious_transpose(A, M,N);

  // Also added column reversal to rotate the matrix.
  result = reverse_columns(result, M, N);

  // for(unsigned i=M-5; i<M; ++i){
  //     for(unsigned j=N-5; j<N; ++j)
  //       std::cout<<result[i * N + j]<<" ";
  //     std::cout<<std::endl;
  // }

  free(result);

  return 0;


}
