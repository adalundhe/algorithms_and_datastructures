#include <iostream>
#include <vector>


int binary_search(const std::vector<int> data, const int low, const unsigned high, const unsigned query){

  if (low > high)
    return -1;

  unsigned mid = (low + high)/2;
  if(data.at(mid) == query) return mid;

  if(data.at(low) <= data.at(mid)){

    if(query >= data.at(low) && query <= data.at(mid))
      return binary_search(data, low, mid-1, query);

    return binary_search(data, mid+1, high, query);
  }

  if(query >= data.at(mid) && query <= data.at(high))
    return binary_search(data, mid+1, high, query);

  return binary_search(data, low, mid-1, query);

}


int main(){
  std::vector<int> data = {4, 5, 6, 7, 8, 9, 1, 2, 3};
  int size = data.size();
  int key = 6;

  int result = binary_search(data, 0, size-1, key);

  std::cout<<"Found at index: "<<result<<std::endl;

  return 0;
}
