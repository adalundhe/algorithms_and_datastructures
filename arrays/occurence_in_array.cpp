#include <vector>
#include <iostream>

int binary_search(std::vector<int> array, unsigned left, unsigned right, int query){
  if(right < left)
    return -1;

  unsigned split = left + (right - left)/2;

  if(array.at(split) == query)
    return split;

  if(array.at(split) > query)
    return binary_search(array, left, split-1, query);
  else
    return binary_search(array, split+1, right, query);

}

int count_occurences(std::vector<int> array, int query){

  unsigned count = 0;
  unsigned size = array.size();

  unsigned first_occurence = binary_search(array, 0, size, query);

  if(first_occurence == -1)
    return 0;

  count += 1;

  unsigned left = first_occurence-1;
  while(left >= 0 && array.at(left) == query){
    count++;
    left--;
  }

  unsigned right = first_occurence + 1;
  while(right < size && array.at(right) == query){
      count++;
      right++;
  }

  return count;

}

int main(){

  std::vector<int> array = { 1, 2, 2, 2, 2, 3, 4, 7, 8, 8 };
  int query = 2;

  unsigned count = count_occurences(array, query);

  std::cout<<"Found query: "<<query<<" a total of: "<<count<<" times"<<std::endl;

  return 0;
}
