#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int find_min_max_subset(std::vector<int> data, int k){
	auto max_iterator = std::max_element(data.begin(), data.end());

	int max_index = std::distance(data.begin(), max_iterator);

	int start = data.at(max_index);

	int end = std::accumulate(data.begin(), data.end(), 0);

	int result = 999999;

	while(start <= end){

		int split = (start + end)/2;
		int subset_sum = 0;
		int subset_count = 1;


		for(auto const &number : data){
			if((subset_sum + number) > split){
	subset_sum = number;
	subset_count++;
}
else{
	subset_sum += number;
}
		}
		if(subset_count <= k){
			result = std::min(result, split);
			end = split - 1;
		}
		else
			start = split + 1;
	}

	return result;

}

int main() {

	std::vector<int> data = {12, 34, 67, 90};
	int k = 2;

	int subset_sum = find_min_max_subset(data, k);

	std::cout<<subset_sum<<std::endl;


	return 0;
}
