#ifndef __LINKED_LIST_H_INCLUDED__
#define __LINKED_LIST_H_INCLUDED__

#include <vector>
#include <iostream>

template <typename T>
struct Node{
  T data;
  int index;
  struct Node<T> *next_node;
};

template <typename T>
class LinkedList{
  public:
    LinkedList(){
      head = nullptr;
      tail = nullptr;
      list_length = 0;
    };
    LinkedList(T initial_data){
      head = nullptr;
      tail = nullptr;
      list_length = 0;

      append(initial_data);
    };
    LinkedList(std::vector<T> initial_data){
      head = nullptr;
      tail = nullptr;
      list_length = 0;

      for(auto const &new_data : initial_data) append(new_data);
    };
    void append(T new_data){
      Node<T> *temp = new Node<T>;
      temp->data=new_data;
      temp->index = list_length;
      temp->next_node=nullptr;
      if(head == nullptr)
      {
        head=temp;
        current=temp;
        tail=temp;
        temp=nullptr;
      }
      else
      {
        tail->next_node=temp;
        tail=temp;
      }

      list_length++;
    };
    void append(std::vector<T> new_data){
      for(auto const &data : new_data) append(data);
    };
    void prepend(T new_data){
      Node<T> *temp = new Node<T>;
      temp->data=new_data;
      temp->next_node=head;
      head=temp;
    };
    void prepend(std::vector<T> new_data){
      for(auto const &data : new_data) prepend(data);
    };
    void insert(T data, int position){
      Node<T> *previous = new Node<T>;
      Node<T> *temp = new Node<T>;

      go_to_head();

      for(int current_position=1; current_position<position; current_position++)
      {
        if(has_next()){
          previous=current;
          get_next();
        }
      }
      temp->data=data;
      temp->index = list_length;
      temp->next_node=current;
      previous->next_node=temp;

      list_length++;
    };
    T find(T query){

      go_to_head();

      while(has_next()){

        if(current->data == query) return current->data;
        get_next();

      }

      return T();

    };
    int index(T query){
      go_to_head();

      while(has_next()){

        if(current->data == query) return current->index;
        get_next();

      }

      return -1;
    };
    int at(int query_index){
      go_to_head();

      while(has_next()){

        if(current->index == query_index) return current->data;
        get_next();

      }

      return T();
    };
    T data(){

      if(current != nullptr) return current->data;

      return T();
    };
    int position(){
      if(current != nullptr) return current->index;
      return 0;
    };
    int length(){
      return list_length;
    };
    bool end(){
      return current == nullptr;
    };
    void advance(){
      get_next();
    };
    void reset(){
      go_to_head();

      for(int index=0; index<list_length; index++){
        current->index = index;
        current = current->next_node;
      }

      go_to_head();
    };
    void swap(int position_a, int position_b){

      if(position_a == position_b) return;

      if(position_a < 0 || position_b < 0) return;
      if(position_a >= list_length || position_b >= list_length) return;

      Node<T> *prev_a = nullptr;
      Node<T> *curr_a  = head;

      for(int i=0; i<position_a; i++){
        prev_a = curr_a;
        curr_a = curr_a->next_node;
      }

      Node<T> *prev_b = nullptr;
      Node<T> *curr_b = head;

      for(int i=0; i<position_b; i++){
        prev_b = curr_b;
        curr_b = curr_b->next_node;
      }

      if (curr_a == nullptr || curr_b == nullptr) return;

      if(prev_a != 0)
        prev_a->next_node = curr_b;
      else
        head = curr_b;

      if(prev_b != 0)
        prev_b->next_node = curr_a;
      else
        head = curr_a;


      Node<T> *temp;



      temp = curr_b->next_node;
      curr_b->next_node = curr_a->next_node;
      curr_a->next_node = temp;

    };
    Node<T>* node(){
      return current;
    };
    void clear(){

      current = head;
      head = head->next_node;

      while(head != nullptr){
        delete current->next_node;
        delete current;
        std::cout<<current->index<<std::endl;
        current = head;
        head = head->next_node;
        list_length--;
      }

      delete head;
      delete current->next_node;
      delete current;
      list_length--;
    }
  private:
    int list_length;
    Node<T> *head, *current, *tail;
    bool has_next() {
      return current->next_node != nullptr;
    };
    void get_next(){
      current = current->next_node;
    };
    void go_to_head(){
      if(head != nullptr) current = head;
      else current = nullptr;
    };
};

#endif
