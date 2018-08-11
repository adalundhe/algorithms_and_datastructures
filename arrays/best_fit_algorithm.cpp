#include <iostream>
#include <limits.h>
#include<bits/stdc++.h>

/*
 * Best Fit Algorithm:
 *
 * Pros: Memory utilization is much better than first fit as it
 * searches the smallest free partition first available.
 *
 * Cons: Is processor-heavy and can leave many, usless, small memory
 * segments open.
 */

void best_fit(int number_blocks, int number_processes, int blocks[], int processes[]){

  int allocations[number_processes];

  memset(allocations, -1, sizeof(allocations));

  for(unsigned i=0; i<number_processes; ++i){

    int minimum_size = INT_MAX;
    int best_id = -1;
    for(unsigned j=0; j<number_blocks; ++j){
      if(minimum_size > blocks[j] && processes[i] <= blocks[j]){
          minimum_size = blocks[j];
          best_id = j;
      }
    }

    if(best_id != -1){
      allocations[i] = best_id;
      blocks[best_id] -=  processes[i];
    }


  }

  for(unsigned i=0; i<number_processes; ++i){

      std::cout<<"\nProcess: "<<(i+1)<<"\t\t"<<"Size: "<<processes[i]<<"\t\t";
      if(allocations[i] != -1)
        std::cout<<(allocations[i] + 1);
      else
        std::cout<<"Not Allocated";
      std::cout<<std::endl;
  }


}


int main(){

  int blocks[] = {100, 500, 200, 300, 600};
  int processes[] = {212, 417, 112, 426};

  int number_blocks = sizeof(blocks)/sizeof(blocks[0]);
  int number_processes = sizeof(processes)/sizeof(processes[0]);

  best_fit(number_blocks, number_processes, blocks, processes);

  return 0;
}
