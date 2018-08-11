#include <iostream>

int binary_ceil(int array[], unsigned low, unsigned high, int query){

  unsigned split;

  if(query <= array[low])
    return low;

  if(query > array[high])
    return -1;

  split = (low + high)/2;

  if(array[split] == query)
    return split;

  if(array[split] < query){
    if(split + 1 <= high && query <= array[split + 1])
      return split + 1;
    else
      return binary_ceil(array, split+1, high, query);
  }

  if(split - 1 >= low && query > array[split - 1])
    return split;
  else
    return binary_ceil(array, low, split-1, query);

}

void pancake_flip(int array[], int i){
  int temp = 0;
  int start = 0;

  while(start < i){
    temp = array[start];
    array[start] = array[i];
    array[i] = temp;

    start++;
    i--;
  }

}

void insertion_sort(int array[], unsigned size){
  int index_i = 0;
  int index_j = 0;

  for(index_i=1; index_i<size; index_i++){

    index_j = binary_ceil(array, 0, index_i-1, array[index_i]);

    if(index_j != -1){
      pancake_flip(array, index_j-1);
      pancake_flip(array, index_i-1);
      pancake_flip(array, index_i);
      pancake_flip(array, index_j);
    }

  }

}

int main(){

  int array[] = {18, 40, 35, 12, 30, 35, 20, 6, 90, 80};
  unsigned size = sizeof(array)/sizeof(int);

  insertion_sort(array, size);

  for(unsigned i=0; i<size; i++)
    std::cout<<array[i]<<std::endl;

  return 0;
}
