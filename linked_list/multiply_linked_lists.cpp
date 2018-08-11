#include "linked_list.h"
#include <iostream>

LinkedList<long long int> multiply_lists(LinkedList<long long int> number_one, LinkedList<long long int> number_two){

  LinkedList<long long int> result_list;
  long long int n_1 = 0;
  long long int n_2 = 0;

  while (true) {

    if(number_one.end() && number_two.end())
      break;

    if(!number_one.end()){
      n_1 = (n_1 * 10) + number_one.data();
      number_one.advance();
    }

    if(!number_two.end()){
      n_2 = (n_2 * 10) + number_two.data();
      number_two.advance();
    }

  }

  long long int result_number = n_1 * n_2;

  result_list.append(result_number);

  return result_list;

}

int main(){

  LinkedList<long long int> number_one;
  std::vector<long long int> number_one_data = {1, 2, 3};
  number_one.append(number_one_data);

  LinkedList<long long int> number_two;
  std::vector<long long int> number_two_data = {2, 3};
  number_two.append(number_two_data);

  LinkedList<long long int> result_list = multiply_lists(number_one, number_two);

  while(!result_list.end()){

      std::cout<<"The product is: "<<result_list.data()<<std::endl;
      result_list.advance();
  }

  return 0;
}
