#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

/*
 * Hybird Selection-Merge Sort.
*/

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int arr[], int array_size){

    int i;

    int iters = array_size;


    for(i=0; i<iters-1; i++){

        int min_index = i;

        for(int j = i + 1; j<iters; j++)
            if(arr[min_index] > arr[j])
                min_index = j;

        swap(&arr[min_index], &arr[i]);
    }

}

void Merge(int *A, int left, int mid, int right) {
	int i,j,k;
  int left_size = mid - left + 1;
  int right_size = right - mid;
  int L[left_size], R[right_size];

  for (i = 0; i < left_size; i++)
        L[i] = A[left + i];

    for (j = 0; j < right_size; j++)
        R[j] = A[mid + 1+ j];

	// i - to mark the index of left aubarray (L)
	// j - to mark the index of right sub-raay (R)
	// k - to mark the index of merged subarray (A)

	i = 0; j = 0; k =left;

	while(i<left_size && j< right_size) {
		if(L[i]  <= R[j])
        A[k++] = L[i++];
		else
      A[k++] = R[j++];
	}
	while(i < left_size) A[k++] = L[i++];
	while(j < right_size) A[k++] = R[j++];

}
void MergeSort(int *A,int n) {

  int current_size = 0;
  int left_start = 0;
	int SWITCH_SORT_SIZE = 64;

  for(current_size=1; current_size <= n-1; current_size *= 2){
    for(left_start=0; left_start<n-1; left_start += 2 * current_size){
      int mid = left_start + current_size - 1;
      int right_end = std::min(left_start + (2 * current_size) - 1 , n-1);
      Merge(A, left_start, mid, right_end);
    }
  }

}

void create_data(int a[],int n)
{
    for(int i = 0; i < n;i++) a[i] = rand() % 50 + 1;
}
void return_result(int a[],int n)
{
    for(int i = 0; i < n;i++)
    {
        std::cout<<a[i]<<" ";
    }
   std::cout<<std::endl;
}
int main() {
	//code
  //
	int n = 10;
	int  arr[n];
	srand(0);
  //
  // int arr[] = {12, 11, 13, 5, 6, 7};
  // int n = sizeof(arr)/sizeof(arr[0]);

	create_data(arr,n);

	MergeSort(arr, n);

	return_result(arr, n);

	return 0;
}
