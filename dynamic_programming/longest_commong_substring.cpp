#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>

std::string longest_suffix(std::string string_a, std::string string_b){
  unsigned m = string_a.length();
  unsigned n = string_b.length();
  unsigned i = 0;
  unsigned j = 0;

  int LCStable[m+1][n+1];

  for(i=0; i<=m; i++){
    for(j=0; j<=n; j++){
      if( i==0 || j ==0 )
        LCStable[i][j] = 0;
      else if(string_a[i-1] == string_b[j-1])
        LCStable[i][j] = LCStable[i-1][j-1] + 1;
      else
        LCStable[i][j] = std::max(LCStable[i-1][j], LCStable[i][j-1]);
    }
  }

  unsigned backtrack_index = LCStable[m][n];

  std::string result(backtrack_index+1, ' ');

  i=m;
  j=n;

  while(i > 0 && j > 0){
    if(string_a[i-1] == string_b[j-1]){
      result[backtrack_index-1] = string_a[i-1];

      i--;
      j--;
      backtrack_index--;

    }
    else if(LCStable[i-1][j] > LCStable[i][j-1])
      i--;
    else
      j--;
  }

  return result;

}


int main(){
  std::string string_a = "AGGTAB";
  std::string string_b = "GXTXAYB";

  std::string result = longest_suffix(string_a, string_b);

  std::cout<<"GOT: "<<result<<std::endl;

  return 0;

}
