#include <iostream>
#include <vector>

void print_answer(const std::vector<int> data, int position_found){
    if(position_found < 0)
    	std::cout<<"Item was not found..."<<std::endl;
	else
		std::cout<<"Item: "<<data.at(position_found)<<" at index: "<<position_found<<std::endl;

}

int binary_search(const std::vector<int> data, const unsigned length, const unsigned query){
    unsigned offset = 0;
    unsigned split = 0;
    unsigned right_index = 0;

    right_index = length-1;

    while(offset <= right_index){
        split = (offset + right_index)/2;

        if(data.at(split) == query){
            return split;
        }
        else{
            if(data.at(split) < query)
            	offset = split + 1;
            else
            	right_index = split - 1;
        }
    }

    return -1;
}

int main() {

	const std::vector<int> data = {1, 3, 4, 7, 8, 9, 11};

	const unsigned length = data.size();
	const unsigned query = 1;

	int position_found = binary_search(data, length, query);

	print_answer(data, position_found);

	return 0;
}
