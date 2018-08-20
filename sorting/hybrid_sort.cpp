#include <iostream>
#include <stdlib.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

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

void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
	int i,j,k;

	// i - to mark the index of left aubarray (L)
	// j - to mark the index of right sub-raay (R)
	// k - to mark the index of merged subarray (A)
	i = 0; j = 0; k =0;

	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]) A[k++] = L[i++];
		else A[k++] = R[j++];
	}
	while(i < leftCount) A[k++] = L[i++];
	while(j < rightCount) A[k++] = R[j++];
}

void MergeSort(int *A,int n) {

	int SWITCH_SORT_SIZE = 64;
	int mid,i;
	if(n < 2) return;

	mid = n/2;

	int L[mid], R[n- mid];

	for(i = 0;i<mid;i++) L[i] = A[i];
	for(i = mid;i<n;i++) R[i-mid] = A[i];

	if(n <= SWITCH_SORT_SIZE){
	  selection_sort(A, n);
	}
	else{
	  MergeSort(L,mid);
	  MergeSort(R,n-mid);
	  Merge(A,L,mid,R,n-mid);
	}
}

void create_data(int a[],int n)
{
    for(int i = 0; i < n;i++) a[i] = rand() % 1000 + 1;
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

	int n = 10000;
	int  arr[n];
	srand(0);

	create_data(arr,n);

	MergeSort(arr, n);

	return_result(arr, n);

	return 0;
}
