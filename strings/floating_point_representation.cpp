#include <string>
#include <bitset>
#include <iostream>
#include <cmath>

int get_power(int a, int b){
  return std::pow(a, b);

}

int find_nearest_power_two(int num){

  int count = 0;

  while(num > 1){
    num /= 2;
    count++;
  }

  return count;

}

std::string calculate_sign(int a){
  return (a >= 0) ? "0" : "1";
}

std::string calculate_exponent(int a, int b){
  int bias = 127;
  int power_result = get_power(a, b);

  int power = find_nearest_power_two(power_result);

  return std::bitset<8>(power + bias).to_string();
}

std::string calculate_mantissa(int a, int b){
  int power_result = get_power(a, b);
  int power = find_nearest_power_two(power_result);
  std::string binary_string = std::bitset<23>(power_result).to_string();
  int string_length = binary_string.size();
  int offset = string_length-power;

  std::string result =  binary_string.substr(offset, std::string::npos);

  while(result.length() < 23)
    result += "0";

  return result;
}


std::string calculated_power_to_float(int a, int b){

  std::string sign = calculate_sign(a);
  std::string exponent = calculate_exponent(a, b);
  std::string mantisa = calculate_mantissa(a, b);

  return ("+"+sign + " "+exponent+" "+mantisa);

}

int main(){

  std::string result = calculated_power_to_float(3, 3);

  std::cout<<result<<std::endl;

  return 0;
}
