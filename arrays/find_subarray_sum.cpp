#include <vector>
#include <unordered_map>
#include <iostream>

std::vector<std::pair<int, int>> find_subarrays(int numbers[], int N, int target_sum){
  /*
   * First find all subarrays with zero sum.
   */

  std::unordered_map<int, std::vector<int>> sum_hash;

  std::vector<std::pair<int, int>> subset_index_ranges;

  int current_sum = 0;
  int index = 0;

  for(index=0; index<N; ++index){

    current_sum += numbers[index];

    if(current_sum == target_sum)
      subset_index_ranges.push_back(std::make_pair(0, index));

    if(sum_hash.find(current_sum) != sum_hash.end()){

        std::vector<int> index_list = sum_hash[current_sum];

        for(auto const &subset_index : index_list)
          subset_index_ranges.push_back(std::make_pair(subset_index+1, index));

    }

    sum_hash[current_sum].push_back(index);

  }

  return subset_index_ranges;

}

std::vector<std::pair<int, int>> get_k_size_subsets(std::vector<std::pair<int, int>> subset_indexes, int k){

  std::vector<std::pair<int, int>> k_size_subsets;

  for(auto const &indexes : subset_indexes)
    if ((indexes.second - indexes.first) == (k - 1))
      k_size_subsets.push_back(std::make_pair(indexes.first, indexes.second));

  return k_size_subsets;

}



void print(std::vector<std::pair<int, int>> out) {
    for (auto const &pair : out)
        std::cout << "Subarray found from Index " <<
            pair.first << " to " << pair.second << std::endl;
}


int main(){

  int arr[] = {6, 3, -1, -3, 4, -2, 2, 4, 6, -12, -7, -1, 1};
  int n = sizeof(arr)/sizeof(arr[0]);

  std::vector<std::pair<int, int>> subset_indexes = find_subarrays(arr, n, 0);

  std::vector<std::pair<int, int>> k_size_subsets = get_k_size_subsets(subset_indexes, 3);

  print(k_size_subsets);

  return 0;
}
