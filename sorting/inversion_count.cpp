#include <iostream>
#include <stdlib.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

/*
 * Hybird Selection-Merge Sort.
*/

int Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
	int i, j, k;
	unsigned long int inversion_count = 0;

	// i - to mark the index of left aubarray (L)
	// j - to mark the index of right sub-raay (R)
	// k - to mark the index of merged subarray (A)
	i = 0; j = 0; k = 0;

	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]){
		  A[k++] = L[i++];
		}
		else{
		  A[k++] = R[j++];
		  
		  inversion_count = inversion_count + (leftCount - i);
		}
	}
	while(i < leftCount) A[k++] = L[i++];
	while(j < rightCount) A[k++] = R[j++];

	return inversion_count;
}

int MergeSort(int *A,int n) {

	int SWITCH_SORT_SIZE = 64; 
	int mid,i;
	if(n < 2) return 0;

	unsigned long int inversion_count = 0;

	mid = n/2;

	int L[mid], R[n- mid];  
	
	for(i = 0;i<mid;i++) L[i] = A[i];
	for(i = mid;i<n;i++) R[i-mid] = A[i];

	inversion_count = MergeSort(L,mid);
	inversion_count += MergeSort(R,n-mid);
	inversion_count += Merge(A,L,mid,R,n-mid);

	return inversion_count;
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

	unsigned int n = 100000;
	int  arr[n];
	srand(0);

	create_data(arr,n);

	unsigned long int inversion_count = MergeSort(arr, n);

        std::cout<<"COUNT: "<<inversion_count<<std::endl;	

	//return_result(arr, n);       

	return 0;
}
