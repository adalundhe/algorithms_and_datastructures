#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

void find_abs_pairs(std::vector<int> number){
  int length = number.size();
  std::unordered_map<int, int> count_hash;
  std::vector<std::pair<int, int>> postive_negative_pairs;

  for(auto const &num : number){

    int abs_num = std::abs(num);

    if(count_hash.find(abs_num) != count_hash.end())
      count_hash[abs_num]++;
    else
      count_hash[abs_num] = 1;
  }

  for(auto const &found_number : count_hash)
    if(found_number.second > 1)
      postive_negative_pairs.push_back(
        std::make_pair(
          found_number.first * -1,
          found_number.first
        )
      );

  if(postive_negative_pairs.size() < 1)
    std::cout<<0<<std::endl;
  else
    for(auto const & pair : postive_negative_pairs)
      std::cout<<pair.first<<" "<<pair.second<<std::endl;

}


int main() {

  std::vector<int> data = {4, 8, 9, -4, 1, -1, -8, -9, 5};

  find_abs_pairs(data);

	return 0;
}
