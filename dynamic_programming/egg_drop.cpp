#include <algorithm>
#include <limits.h>
#include <iostream>

int calculate_number_of_trials(int eggs, int floors){
  if(floors == 1 || floors ==0)
    return floors;

  if(eggs == 1) return floors;

  unsigned min = UINT_MAX;
  unsigned number_of_trials = 0;

  for(unsigned i=1; i<floors; i++){
    number_of_trials = std::max(
      calculate_number_of_trials(eggs-1, i-1),
      calculate_number_of_trials(eggs, floors-i)
    );
    if(number_of_trials < min)
      min = number_of_trials;
  }

  return min + 1;

}

int main(){
  unsigned floors = 35;
  unsigned eggs = 4;

  int result = calculate_number_of_trials(eggs, floors);

  std::cout<<"GOT: "<<result<<std::endl;

}
