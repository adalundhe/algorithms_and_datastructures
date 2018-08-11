#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <vector>


std::vector<std::string> get_classification_string(std::string string_in){

  int string_size = string_in.length();

  std::vector<std::string> classification_string(string_size);

  for(unsigned i=0; i<string_size-1; i++){
    if(string_in[i] != string_in[i+1]){
      if(string_in[i] < string_in[i+1])
        classification_string[i] = "S";
      else
        classification_string[i] = "L";
    }
    else{
      unsigned j = i;
      while(j < string_size-1){
        if(string_in[i] != string_in[j]){
          if(string_in[j] > string_in[i-1])
            for(unsigned k=i; k<j; k++)
              classification_string[k] = "S";
          else
            for(unsigned k=i; k<j; k++)
              classification_string[k] = "L";

          classification_string[j] ='_';

          break;
        }
        j++;
      }
    }
  }


  classification_string[string_size-1] = "L/S";

  return classification_string;
}

void bucket_s_types(std::string string_in, std::vector<std::string> classification_string){

  int string_size = string_in.length();
  std::map<char, std::vector<int>> buckets;
  std::map<char, std::vector<int>>::iterator it;

  for(int i=string_size-1; i>=0; --i){

    char c = string_in[i];

    if(buckets.find(c) != buckets.end()){
      buckets[c].push_back(i+1);
    }
    else{

      std::vector<int> suffix_locations;
      suffix_locations.push_back(i+1);

      buckets[c] = suffix_locations;

    }
  }

  std::string swapped_string = "";

  for ( it = buckets.begin(); it != buckets.end(); it++ ){

    char c = it->first;
    std::vector<int> positions = it->second;
    std::sort(positions.begin(), positions.end());

    buckets[c] = positions;

    for(auto const &index : positions){
      swapped_string += c;
      std::cout<<index<<std::endl;
    }
  }

  std::cout<<swapped_string<<std::endl;


}

int main(){

  std::string input_string = "MISSISSIPPI";
  input_string += "$";
  std::vector<std::string> classification_string = get_classification_string(input_string);

  for(auto const &c : classification_string)
    std::cout<<c<<" ";
  std::cout<<std::endl;

  bucket_s_types(input_string, classification_string);

  return 0;
}
