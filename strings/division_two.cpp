#include <map>
#include <string>
#include <iostream>

std::string find_repeating_sequence(int numerator, int denominator, unsigned *position){
  std::string result;

  std::map<int, int> remainder_store;
  remainder_store.clear();

  int remainder_amount = numerator%denominator;


  while(remainder_amount != 0 && remainder_store.find(remainder_amount) == remainder_store.end()){

    remainder_store[remainder_amount] = result.length();

    remainder_amount = remainder_amount * 10;

    int resultant_remainder = remainder_amount/denominator;

    result += std::to_string(resultant_remainder);

    remainder_amount = remainder_amount % denominator;

    *position += 1;

  }

  return (remainder_amount == 0) ? "" :  result.substr(remainder_store[remainder_amount]);

}

std::string merge_remainder_and_repeating(std::string remainder_string, std::string repeating_string){
  std::string merged_result = "";

  unsigned length_a = remainder_string.length();
  unsigned length_b = repeating_string.length();

  unsigned iteration_limit = (length_a < length_b) ? length_a : length_b;

  std::string non_repeating = "";

  unsigned index = 0;
  for(auto const &c : remainder_string){
    if(c == repeating_string[index] && index < iteration_limit){
        merged_result += c;
    }
    else{
      merged_result += remainder_string[index];
    }

    index += 1;
  }

  if (index < length_b)
    non_repeating = "(" + repeating_string.substr(index, length_b-index) + ")";
  else
    non_repeating = "(" + repeating_string + ")";

  merged_result += non_repeating;

  return merged_result ;

}

std::string divide(int numerator, int denominator){

  bool is_negative = false;

  if(numerator < 0){
    is_negative = !is_negative;
    numerator = numerator * -1;
  }
  if(denominator < 0){
    is_negative = !is_negative;
    denominator = denominator * -1;
  }

  std::string string_quotient = "";
  std::string repeating_amount = "";

  unsigned repeating_number_position = 0;

  repeating_amount = find_repeating_sequence(numerator, denominator, &repeating_number_position);

  repeating_number_position -= 1;

  if(is_negative) string_quotient = '-' + string_quotient;


  if(repeating_amount == ""){
    double quotient = numerator/denominator;
    string_quotient = std::to_string(quotient);
    return string_quotient;
  }
  else{
    float quotient = (float)numerator/(float)denominator;
    string_quotient = std::to_string(quotient);
    std::string::size_type loc = string_quotient.find( ".", 0 );
    std::string remainder_amount = string_quotient.substr(loc+1);
    remainder_amount = remainder_amount.substr(0, remainder_amount.length()-1);

    if((repeating_amount.find(remainder_amount) == std::string::npos) || repeating_amount.length() > remainder_amount.length())
      return string_quotient.substr(0, loc) + string_quotient.substr(loc, 1) + merge_remainder_and_repeating(remainder_amount, repeating_amount);
    else
      return string_quotient.substr(0, loc) + string_quotient.substr(loc, 1) + "(" + repeating_amount + ")";
  }
}

int main(){

  std::string quotient = "";

  quotient = divide(94, 95);

  std::cout<<quotient<<std::endl;

  return 0;
}
