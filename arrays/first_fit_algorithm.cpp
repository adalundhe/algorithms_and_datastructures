#include <iostream>
#include <limits.h>
#include<bits/stdc++.h>

/*
 * First Fit Algorithm:
 *
 * Pros: Fast and a good 2*n approximation.
 *
 * Cons: May be unable to fit processes that would otherwise
 * have space to be allocated due to greedily packing.
 *
 */

void first_fit(int number_blocks, int number_processes, int blocks[], int processes[]){

  int allocations[number_processes];

  memset(allocations, -1, sizeof(allocations));

  for(unsigned i=0; i<number_processes; i++)
    for(unsigned j=0; j<number_blocks; j++)
      if(blocks[j] >= processes[i]){
          allocations[i] = j;
          blocks[j] -= processes[i];
          break;
      }

    for(unsigned k=0; k<number_processes; ++k){
      std::cout<<"\nProcess: "<<(k+1)<<"\t\t"<<"Size: "<<processes[k]<<"\t\t";
      if(allocations[k] != -1)
        std::cout<<(allocations[k] + 1);
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

  first_fit(number_blocks, number_processes, blocks, processes);

  return 0;
}
