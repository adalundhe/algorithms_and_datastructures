#include <stdlib.h>
#include <iostream>

struct Box{
  int w=0;
  int h=0;
  int d=0;
};

int compare(const void *a, const void *b){
  return ((*(Box *)b).d * (*(Box *)b).w) - ((*(Box *)a).d * (*(Box *)a).w);
}

int max_stack_height(Box arr[], int n){

  Box rotation_array[3 * n];
  int index=0;

  for(int i=0; i<n; ++i){
    rotation_array[index].h = arr[i].h;
    rotation_array[index].d = std::max(arr[i].d, arr[i].w);
    rotation_array[index].w = std::min(arr[i].w, arr[i].d);
    index++;

    rotation_array[index].h = arr[i].w;
    rotation_array[index].d = std::max(arr[i].h, arr[i].d);
    rotation_array[index].w = std::min(arr[i].h, arr[i].d);
    index++;

    rotation_array[index].h = arr[i].d;
    rotation_array[index].d = std::max(arr[i].h, arr[i].w);
    rotation_array[index].w = std::min(arr[i].h, arr[i].w);
    index++;

  }

  n = 3 * n;

  qsort(rotation_array, n, sizeof(rotation_array[0]), compare);

  int maximum_stack[n];

  for(unsigned i=0; i<n; ++i)
    maximum_stack[i] = rotation_array[i].h;

  for(unsigned i=1; i<n; ++i)
    for(unsigned j=0; j<n; ++j)
      if(rotation_array[i].w < rotation_array[j].w &&
        rotation_array[i].d < rotation_array[j].d &&
        maximum_stack[i] < maximum_stack[j] + rotation_array[i].h
      ){
        maximum_stack[i] = maximum_stack[j] + rotation_array[i].h;
      }

  int max = -1;

  for(unsigned i=0; i<n; ++i)
    if(max < maximum_stack[i])
      max = maximum_stack[i];

  return max;

}

int main(){

  Box arr[] = { {4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32} };
  int n = sizeof(arr)/sizeof(arr[0]);

  int result = max_stack_height(arr, n);

  std::cout<<result<<std::endl;

  return 0;
}
