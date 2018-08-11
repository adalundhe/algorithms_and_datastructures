#include <unordered_map>
#include <utility>
#include <cmath>
#include <iostream>
#include <string>

int atoi(std::string str)
{
    std::unordered_map<char, int> char_map;
    std::string integer_string = "";

    for(int i=0; i<10; ++i){
        char c;
        sprintf(&c, "%d", i);
        char_map.insert(
            std::make_pair(c, i)
        );
    }

    int count = 0;
    int result = 0;
    int sign = 1;

    if(str[0] == '-'){
        integer_string = str.substr(1, str.length()-1);
        sign = -1;
    }
    else
        integer_string = str.substr(0, str.length());

    int length = integer_string.length()-1;

    for(int i=length; i>= 0; --i)
      if(char_map.find(integer_string[i]) == char_map.end())
        return -1;
      else{
        result += char_map[integer_string[i]] * std::pow(10, count);
        count++;
      }

    return result * sign;
}

int main(){
  std::string test = "-0a";

  int result = atoi(test);

  std::cout<<result<<std::endl;

  return 0;
}
