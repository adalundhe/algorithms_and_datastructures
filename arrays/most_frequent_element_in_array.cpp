#include <iostream>

unsigned get_most_frequest_element(int arr[], int N, int k){

  for(unsigned i=0; i<N; ++i)
    arr[arr[i]%k] += k;

  int max_index = 0;

  for(unsigned i=1; i<N; ++i)
    if(arr[i] > arr[max_index])
      max_index = i;

  return max_index;
}

int main(){

  int arr[] = {2, 3, 3, 5, 3, 4, 1, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 8;

    std::cout << "The maximum repeating number is " <<
         get_most_frequest_element(arr, n, k) << std::endl;

  return 0;
}
