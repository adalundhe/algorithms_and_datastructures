#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#define N 10

void Merge(int *A, int *L, int leftMark, int* R, int rightMark){
	int i, j, k;
	
	i=0; j=0; k=0;
	
	while(i<leftMark && j<rightMark){
	  if(L[i] < R[j]) A[k++] = L[i++];
	  else A[k++] = R[j++];
	}
	while(i < leftMark) A[k++] = L[i++];
	while(j<rightMark) A[k++] = R[j++];

}

void MergeSort(int A[], int n){
	if(n < 2) return;
	
	int i;
	int mid = n/2;
        
        int L[mid];
	int R[n - mid];

        for(i=0; i<mid; i++) L[i] = A[i];
	for(i=mid; i<n; i++) R[i-mid] = A[i];
	
	MergeSort(L, mid);
	MergeSort(R, n-mid);
	Merge(A, L, mid, R, n-mid);
}

void PrintData(int* A){
  for(int i=0; i<N; i++) std::cout<<A[i]<<" ";
}

void CreateData(int A[]){
  srand(0);

  for(int i=0; i<N; i++) A[i] = rand()%N + 1;
}

void AltSort(int A[]){
  int i =0;
  int j = N-1;
  
  std::vector<int> altSorted;
  
  while (i < j) {

    int max = A[j--];
    int min = A[i++];

    altSorted.push_back(max);
    altSorted.push_back(min);
  }
 
  if (N % 2 != 0) altSorted.push_back(A[i]);

  for(i=0; i<N; i++) A[i] = altSorted.at(i);

  std::cout<<"\n"<<"ALT SORTED:"<<std::endl;
  PrintData(A);

}

int main(){
  // 1.) sort
  
  int A[N];
  CreateData(A);

  MergeSort(A, N);
  PrintData(A);

  // 2.) advance min/max pointers and print array
  AltSort(A);

  return 0;
}
