#include <vector>
#include <iostream>
#include <algorithm>
#define M 3
#define N 3

int max_of_three(int a, int b, int c){

  return std::max(a, std::max(b, c));
}

int maximum_sum_path(int matrix[][M]){

  for(unsigned i=1; i<N; i++){
    for(unsigned j=0; j<M; j++){
        if(j > 0 && j < M-1)
          matrix[i][j] += std::max(
            matrix[i-1][j],
            std::max(matrix[i-1][j-1],
            matrix[i-1][j+1])
          );
        else if (j > 0)
          matrix[i][j] += std::max(
            matrix[i-1][j],
            matrix[i-1][j-1]
          );
        else if (j < M-1)
          matrix[i][j] += std::max(
            matrix[i-1][j],
            matrix[i-1][j+1]
          );
    }
  }


    int result = 0;

    for(unsigned k=0; k<M; ++k)
      result = std::max(matrix[N-1][k], result);

    return result;

}


int main(){

  int matrix[N][M] = {
    {1, 2, 3},
    {9, 8, 7},
    {4, 5, 6}
  };

  int result = maximum_sum_path(matrix);

  std::cout<<"The value of the maximum sum path is: "<<result<<std::endl;

  return 0;
}
