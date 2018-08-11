#include <iostream>
#include <stdlib.h>
#include <time.h>
#define N 1000

void PrintData(int A[]){

  for(int i=0; i<N; i++) std::cout<<A[i]<<" ";

  std::cout<<std::endl;  

}

void Swap(int *a, int *b){

  int temp = *a;
  *a = *b;
  *b = temp;

}

void SelectionSort(int A[]){

  int i;

  for(i=0; i<N-1; i++){
    int minIndex = i;
    
    for(int j=i; j<N; j++)
	if(A[minIndex] > A[j])
		minIndex = j;


    Swap(&A[minIndex], &A[i]);
  }

}

void CreateData(int A[]){
  srand(0);

  for(int i=0; i<N; i++) A[i] = rand()%N + 1;

}

int main(){

  int A[N];

  CreateData(A);
  SelectionSort(A);  
  PrintData(A);

}
