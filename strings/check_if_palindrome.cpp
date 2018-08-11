#include <string>
#include <iostream>


bool is_palindrome(std::string candidate){
  unsigned start = 0;
  unsigned end = candidate.length()-1;

  while(start < end){
    if(candidate[start] != candidate[end])
      return false;

    start++;
    end--;
  }

  return true;

}


int main(){

  std::string candidate = "geeks";

  bool palindrome_result = is_palindrome(candidate);

  if(palindrome_result)
    std::cout<<"Candidate: "<<candidate<<" is a palindrome."<<std::endl;
  else
    std::cout<<"Candidate: "<<candidate<<" is not a palindrome."<<std::endl;

  return 0;
}
