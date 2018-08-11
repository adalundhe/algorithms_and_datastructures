#include <iostream>
#include <algorithm>

int find_rain_water(int buckets[], int N){
  int left_walls[N];
  int right_walls[N];

  int total_water_amount = 0;
  int i=0;

  left_walls[0] = buckets[0];

  for(i=1; i<N; ++i)
    left_walls[i] = std::max(left_walls[i-1], buckets[i]);

  right_walls[N-1] = buckets[N-1];

  for(i=N-2; i>=0; --i)
    right_walls[i] = std::max(right_walls[i+1], buckets[i]);

  for(i=0; i<N; ++i)
    total_water_amount += std::min(left_walls[i], right_walls[i]) - buckets[i];

  return total_water_amount;

}


int main(){

  int arr[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  int n = sizeof(arr)/sizeof(arr[0]);
  std::cout << "Maximum water that can be accumulated is "
       << find_rain_water(arr, n)<<std::endl;

  return 0;
}
