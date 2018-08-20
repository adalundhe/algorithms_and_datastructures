#include <iostream>
#include <cmath>

int min_dist_to_target(int target){

  int abs_target = std::abs(target);
  int sum = 0;
  int step = 0;

  while(sum < abs_target || (sum-abs_target)%2 != 0){
    step++;
    sum += step;
  }

  return step;
}

int main(){

  int target = -19;
  int result = min_dist_to_target(target);

  std::cout<<"Minimum steps to target is: "<<result<<std::endl;

  return 0;
}
