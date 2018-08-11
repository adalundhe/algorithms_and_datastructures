#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#define MAX_RLEN 255

std::string encode(std::string source){
  int run_length = 0;
  char count[MAX_RLEN];
  int str_length = source.length();

  std::string destination("", str_length*2 + 1);

  unsigned i=0;
  unsigned j=0;
  unsigned k=0;

  for(i=0; i<str_length; ++i){
    destination[j++] = source[i];

    run_length = 1;

    while(i+1 < str_length && source[i] == source[i+1]){
      run_length++;
      i++;
    }

    sprintf(count, "%d", run_length);

    for(k=0; *(count+k); ++k, ++j)
      destination[j] = count[k];

  }

  destination[j] = '\0';

  return destination;

}


int main(){

  std::string test = "geeksforgeeks";
  std::string result = encode(test);

  std::cout<<result<<std::endl;

  return 0;
}
