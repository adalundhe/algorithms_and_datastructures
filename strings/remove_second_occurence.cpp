#include <iostream>
#include <unordered_map>
#include <string>

std::unordered_map<char, int> generate_char_map(std::string sequence){
  std::unordered_map<char, int> char_map;

  for(auto const &c : sequence)
    char_map[c] = 0;

  return char_map;

}

std::string remove_secondary_occurences(std::string string_in, std::string removal_string){

  std::unordered_map<char, int> char_map = generate_char_map(removal_string);

  std::string result = "";

  for(auto const &c : string_in)
    if(char_map.find(c) == char_map.end())
      result += c;
    else
      if(char_map[c] == 0){
        result += c;
        char_map[c] += 1;
      }

  return result;
}

int main(){

  std::string test_string = "iloveyourdogdude";
  std::string remove_characters = "aeiou";

  std::string result = remove_secondary_occurences(test_string, remove_characters);

  std::cout<<result<<std::endl;

  return 0;
}
