#include <iostream>
#include <stdlib.h>
#include <time.h>
#define N 10

void PrintData(int A[]){

  for(int i=0; i<N; i++) std::cout<<A[i]<<" ";

  std::cout<<std::endl;

}

void Swap(int *a, int *b){
  
  int temp = *a;
  *a = *b;
  *b = temp;

}

// Use Hoare's Partition for x3 less swaps.
int Partition(int A[], int l, int h){

  int pivot = A[l];
  int i = l - 1;
  int j = h + 1;

  while (true){
   
    do{
    
      i++;

    } while(A[i] < pivot);

    do{

      j--;
    
    } while(A[j] > pivot);

    if(i >= j) return j;

    Swap(&A[i], &A[j]);
  
  }
}

// Randomize partition index to help avoid worst case behavior.
int RandomizePartition(int A[], int l, int h){
  
  int randomized_partition = rand()%(h-l) + l;
  
  Swap(&A[randomized_partition], &A[h]);

  return Partition(A, l , h);

}

void QuickSort(int A[], int l, int h){

  if(l < h){

    int next_partition = RandomizePartition(A, l, h);

    QuickSort(A, l, next_partition - 1);
    QuickSort(A, next_partition + 1, h);

  }

}


void CreateData(int A[]){
  srand(0);

  for(int i=0; i<N; i++) A[i] = rand()%N + 1;

}

int main(){
  int A[N];

  CreateData(A);
  std::cout<<"BEFORE: "<<std::endl;
  PrintData(A);
  
  QuickSort(A, 0, N-1);

  std::cout<<"AFTER: "<<std::endl;
  PrintData(A);

}
