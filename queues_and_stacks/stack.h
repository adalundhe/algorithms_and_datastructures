#ifndef __STACK_H_INCLUDE__
#define __STACK_H_INCLUDE__

#include <vector>
#include <iostream>

template <typename T>
class Stack{
  public:
    Stack(const int new_stack_limit);
    Stack(T stack_data, const int new_stack_limit);
    Stack(std::vector<T> new_data, const int new_stack_limit);
    T pop();
    void push(const T new_data);
    T peep() const;
    bool isempty() const;
    bool isfull() const;
    int length() const;
  private:
    std::vector<T> stack_data;
    int stack_length = 0;
    int stack_limit = 0;
};

template <typename T>
Stack<T>::Stack(const int new_stack_limit){
  stack_limit=new_stack_limit;
}

template <typename T>
Stack<T>::Stack(T new_data, const int new_stack_limit){
  stack_limit = new_stack_limit;
  push(new_data);
}

template <typename T>
Stack<T>::Stack(std::vector<T> new_data, const int new_stack_limit){
  stack_limit=new_stack_limit;
  for(auto const &data_item : new_data) push(data_item);
}

template <typename T>
T Stack<T>::pop(){
  if(isempty()) return T();

  int data = stack_data.back();

  stack_data.pop_back();
  stack_length--;

  return data;
}

template <typename T>
void Stack<T>::push(const T new_data){

  if(isfull()) return;

  stack_data.push_back(new_data);
  stack_length++;
}

template <typename T>
int Stack<T>::length() const{
  return stack_length;
}

template <typename T>
T Stack<T>::peep() const{

  int last_index = stack_length-1;

  if(!isempty()) return stack_data.at(last_index);
  else return T();

}

template <typename T>
bool Stack<T>::isempty() const{
  return stack_length == 0;
}

template <typename T>
bool Stack<T>::isfull() const{
  return stack_length == stack_limit;
}


template <typename T>
class MinStack{
  public:
    MinStack(const int new_stack_limit=0);
    MinStack(T stack_data, const int new_stack_limit=0);
    MinStack(std::vector<T> new_data, const int new_stack_limit=0);
    T pop();
    void push(const T new_data);
    T peep() const;
    bool isempty() const;
    bool isfull() const;
    int length() const;
    T getmin() const;
    void setmin(const T new_data);
    bool ismin(const T min_candidate);
  private:
    T minimum_element = 0;
    std::vector<T> stack_data;
    int stack_length = 0;
    int stack_limit = 0;
};

template <typename T>
MinStack<T>::MinStack(const int new_stack_limit){
  stack_limit=new_stack_limit;
}

template <typename T>
MinStack<T>::MinStack(T new_data, const int new_stack_limit){
  stack_limit = new_stack_limit;
  push(new_data);
}

template <typename T>
MinStack<T>::MinStack(std::vector<T> new_data, const int new_stack_limit){
  stack_limit=new_stack_limit;
  for(auto const &data_item : new_data) push(data_item);
}

template <typename T>
T MinStack<T>::pop(){
  if(isempty()) return T();

  int data = stack_data.back();
  int min_candidate = data;

  if(ismin(data)){
    min_candidate = 2 * minimum_element - data;
    data = minimum_element;
    setmin(min_candidate);
  }

  stack_data.pop_back();
  stack_length--;

  return data;
}

template <typename T>
void MinStack<T>::push(const T new_data){

  T new_value = new_data;

  if(isfull()) return;

  if (stack_length == 0){
    setmin(new_value);
  }
  else if(ismin(new_data) && stack_length > 0){
    new_value = 2*new_data - minimum_element;
    setmin(new_data);
  }

  stack_data.push_back(new_value);
  stack_length++;
}

template <typename T>
int MinStack<T>::length() const{
  return stack_length;
}

template <typename T>
T MinStack<T>::peep() const{

  int last_index = stack_length-1;

  if(!isempty()) return stack_data.at(last_index);
  else return T();

}

template <typename T>
bool MinStack<T>::isempty() const{
  return stack_length == 0;
}

template <typename T>
bool MinStack<T>::isfull() const{
  return stack_length == stack_limit;
}

template <typename T>
void MinStack<T>::setmin(const T new_data){
  minimum_element = new_data;
}

template <typename T>
T MinStack<T>::getmin() const{
  return minimum_element;
}

template <typename T>
bool MinStack<T>::ismin(const T min_candidate){
  if(min_candidate < minimum_element) return true;
  else return false;
}

#endif
