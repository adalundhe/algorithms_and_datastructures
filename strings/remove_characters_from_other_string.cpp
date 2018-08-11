#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

std::string remove_in_other(std::string string_one, std::string string_two){

  std::unordered_map<char, int> string_hash;
  std::string result = "";

  for(auto const &c : string_two){
    string_hash[c] += 1;
  }


  for(auto const &c : string_one)
    if(string_hash[c] == 0)
      result += c;

  return result;
}

int main(){

  std::string s_1 = "geeksforgeeks";
  std::string s_2 = "mask";

  std::string result = remove_in_other(s_1, s_2);

  std::cout<<result<<std::endl;

  return 0;
}
