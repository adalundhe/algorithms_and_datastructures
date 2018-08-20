#include <iostream>
#include <vector>
#include <limits.h>

std::pair<int, int> max_sub_array_sum(std::vector<int> array, int size){
  int maximum = INT_MIN;
  int current_max = 0;
  int start = 0;
  int end = 0;
  int current_start = 0;
  int position=0;

  for(auto const &num : array){

      current_max += num;

      if(maximum < current_max){
        maximum = current_max;
        start = current_start;
        end = position;
      }
      if(current_max < 0){
        current_max = 0;
        current_start = position+1;
      }

      position++;

  }

  std::pair<int,int> subset_indices(start, end);

  return subset_indices;

}

int main()
{
    std::vector<int>array = {-2, -3, 4, -1, -2, 1, 5, -3};
    int size = array.size();
    std::pair<int,int>subset_indices = max_sub_array_sum(array, size);

    int sum = 0;

    for(unsigned i=subset_indices.first; i<=subset_indices.second; ++i )
      sum += array[i];

    std::cout<<"The max subset occurs between indices: "<<subset_indices.first<<" and "<<subset_indices.second<<std::endl;
    std::cout<<"The maximum subset sum is: "<<sum<<std::endl;

    return 0;
}
