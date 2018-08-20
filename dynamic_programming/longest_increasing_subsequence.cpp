#include <iostream>

int lcs(int arr[], int n){

  int *longest_increasing_subsequence = (int*)malloc(sizeof(int) * n);
  int maximum = 0;
  int i=0;
  int j=0;

  for(i=0; i<n; ++i)
    longest_increasing_subsequence[i] = 1;

  for(i=1; i<n; ++i)
    for(j=0; j<i; ++j)
      if(arr[i] > arr[j] && longest_increasing_subsequence[i] < longest_increasing_subsequence[j] + 1)
        longest_increasing_subsequence[i] = longest_increasing_subsequence[j] + 1;

  for(i=0; i<n; ++i)
    if(longest_increasing_subsequence[i] > maximum)
      maximum = longest_increasing_subsequence[i];

  return maximum;

}

int main(){

  int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
  int n = sizeof(arr)/sizeof(arr[0]);

  int result = lcs(arr, n);

  std::cout<<"The length of the longest increasing subsequence is: "<<result<<std::endl;

  return 0;
}
