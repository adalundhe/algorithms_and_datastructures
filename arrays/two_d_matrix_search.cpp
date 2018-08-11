#include <utility>
#include <iostream>

std::pair<int, int> search(int matrix[4][4], int N, int query){

  int i=0;
  int j=N-1;

  while (i < N && j >= 0) {

    if(matrix[i][j] == query)
      return std::make_pair(i, j);

    if(matrix[i][j] > query)
      j--;
    else
      i++;

  }

  return std::make_pair(-1, -1);
}

int main(){

  int mat[4][4] = { {10, 20, 30, 40},
                    {15, 25, 35, 45},
                    {27, 29, 37, 48},
                    {32, 33, 39, 50},
                  };

  std::pair<int, int> result = search(mat, 4, 29);

  std::cout<<"Found element at indicies: "<<result.first<<", "<<result.second<<"."<<std::endl;

  return 0;
}
