#ifndef __DOUBLY_LINKED_LIST_H_INCLUDED__
#define __DOUBLY_LINKED_LIST_H_INCLUDED__

#include <vector>
#include <iostream>
#include <time.h>
#include "linked_list.h"
#include <unordered_map>

template <typename T>
struct DoubleNode{
  public:
    T data = T();
    DoubleNode<T> *next = nullptr;
    DoubleNode<T> *prev = nullptr;
    DoubleNode<T> *random = nullptr;
    int index = 0;
};

template <typename T>
class DoublyLinkedList{
  public:
    DoublyLinkedList();
    DoublyLinkedList(T node_data);
    DoublyLinkedList(std::vector<T> node_data);
    void clear();
    void prepend(T node_data);
    void prepend(std::vector<T> node_data);
    void insert(T node_data, unsigned pos);
    void insert(std::vector<T> node_data, unsigned pos);
    void insert(DoubleNode<T> *node, unsigned pos);
    void append(T node_data);
    void append(std::vector<T> node_data);
    void overwrite(DoubleNode<T> *new_node, unsigned pos);
    void reverse();
    T find(T query);
    int index(T query);
    T at(int index);
    void advance();
    void back();
    void reset();
    void tohead();
    void toend();
    bool isend();
    int length();
    void randomize();
    void copy(DoubleNode<T> *from, DoubleNode<T> *to);
    DoubleNode<T> getptr();
    DoubleNode<T> getptr(int query_index);
    T data();
    int position();
    void print();
  private:
    DoubleNode<T> *head = nullptr, *current = nullptr, *tail = nullptr;
    int list_length = 0;
    bool has_next();
    bool has_previous();
    void get_next();
    void get_previous();
    void go_to_head();
    void go_to_end();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(){};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(T node_data){
  append(node_data);
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::vector<T> node_data){
  append(node_data);
}

template <typename T>
void DoublyLinkedList<T>::clear(){
  go_to_head();

  head = head->next;

  while(head != nullptr){
    delete current->random;
    delete current->next;
    delete current->prev;
    delete current;
    std::cout<<current->index<<std::endl;
    current = head;
    head = head->next;
    list_length--;
  }
  std::cout<<current<<std::endl;

  delete head;
  delete current->random;
  delete current->prev;
  delete current->next;
  delete current;

  std::cout<<current->index<<std::endl;
  list_length--;

}

template <typename T>
void DoublyLinkedList<T>::prepend(T node_data){
  DoubleNode<T>* new_node = new DoubleNode<T>;
  new_node->data = node_data;

  new_node->next = head;

  if(list_length == 0) head->prev = new_node;

  head = new_node;

  delete new_node;
  list_length++;
}

template <typename T>
void DoublyLinkedList<T>::prepend(std::vector<T> node_data){
  for(auto const &data : node_data) prepend(data);
}

template <typename T>
void DoublyLinkedList<T>::insert(T node_data, unsigned pos){

  if (pos >= list_length || pos < 0) return;

  DoubleNode<T>* new_node = new DoubleNode<T>;
  new_node->data = node_data;
  new_node->index = pos;

  if(head == nullptr){
    head = new_node;
    current = new_node;
    tail = new_node;
    new_node = nullptr;
    list_length++;
  }
  else if(pos == 0 && head != nullptr){
    prepend(node_data);
  }

  if((pos+1) == list_length){
    append(node_data);
  }
  else{
    go_to_head();
    for(int index=1; index<=pos; index++){
      if(has_next()){
        get_next();
      }
    }

    new_node->next = current;
    new_node->prev = current->prev;
    current->prev->next = new_node;
    current->prev = new_node;

    go_to_head();
    list_length++;
  }

  delete new_node;

  return;

}

template <typename T>
void DoublyLinkedList<T>::insert(std::vector<T> node_data, unsigned pos){
  for(auto const &data_item : node_data){
    insert(data_item, pos);
    pos++;
  }
}

template <typename T>
void DoublyLinkedList<T>::insert(DoubleNode<T> *node, unsigned pos){
  DoubleNode<T>* new_node = new DoubleNode<T>;

  copy(node, new_node);
  delete node;

  if(head == nullptr){
    head = new_node;
    current = new_node;
    tail = new_node;
    new_node = nullptr;
  }
  else if(pos == 0){
    new_node->next = head;

    if(list_length == 0) head->prev = new_node;

    head = new_node;

  }
  else if(pos == list_length){
    new_node->prev = tail;
    tail->next = new_node;
    tail = new_node;
  }
  else{
    while(current->index < pos){
      get_next();
    }

    new_node->next = current;
    new_node->prev = current->prev;
    current->prev->next = new_node;
    current->prev = new_node;
  }

  delete new_node;
  return;
}

template <typename T>
void DoublyLinkedList<T>::append(T node_data){
  DoubleNode<T> *new_node = new DoubleNode<T>;
  new_node->data = node_data;
  new_node->index = list_length;

  if(head == nullptr){
    head = new_node;
    current = new_node;
    tail = new_node;
    new_node = nullptr;
  }
  else{
    new_node->prev = tail;
    tail->next = new_node;
    tail = new_node;
  }

  delete new_node;
  list_length++;
}

template <typename T>
void DoublyLinkedList<T>::append(std::vector<T> node_data){
  for(auto const &data : node_data) append(data);
}

template <typename T>
void DoublyLinkedList<T>::reverse(){
     DoubleNode<T> *temp  = nullptr;
     DoubleNode<T> *current = head;

     while (current !=  nullptr)
     {
       temp = current->prev;
       current->prev = current->next;
       current->next = temp;
       current = current->prev;
     }

     if(temp != nullptr )
        head = temp->prev;
}

template <typename T>
void DoublyLinkedList<T>::overwrite(DoubleNode<T> *new_node, unsigned pos){

  DoubleNode<T> *current_node = head;

  bool is_duplicate = false;
  while(current_node->next != nullptr){
    if(current_node->index == pos && is_duplicate) copy(new_node, current);
    else if(current_node->index == pos) is_duplicate = true;
    else is_duplicate = false;

    current_node = current_node->next;
  }

}

template <typename T>
T DoublyLinkedList<T>::find(T query){
  go_to_head();

  while(has_next()){
    if(current->data == query) return current->data;
    get_next();
  }

  go_to_head();

  return T();
}

template <typename T>
int DoublyLinkedList<T>::index(T query){
  go_to_head();

  while(has_next()){
    if(current->data == query) return current->index;
    get_next();
  }

  go_to_head();

  return -1;
}

template <typename T>
T DoublyLinkedList<T>::at(int query_index){

  if(query_index >= list_length || query_index < 0) return T();

  go_to_head();

  while(has_next()){
    if(current->index == query_index) return current->data;
    get_next();
  }

  go_to_head();

  return T();

}

template <typename T>
void DoublyLinkedList<T>::advance(){
  get_next();
}

template <typename T>
void DoublyLinkedList<T>::back(){
  get_previous();
}

template <typename T>
void DoublyLinkedList<T>::tohead(){
  go_to_head();
}

template <typename T>
void DoublyLinkedList<T>::toend(){
  go_to_end();
}

template <typename T>
void DoublyLinkedList<T>::reset(){
  go_to_head();

  for(int index=0; index<list_length; index++){
    current->index = index;
    advance();
  }

  go_to_head();
}

template <typename T>
bool DoublyLinkedList<T>::isend(){
  return current == nullptr;
}

template <typename T>
int DoublyLinkedList<T>::length(){
  return list_length;
}

template <typename T>
T DoublyLinkedList<T>::data(){
  return current->data;
}

template <typename T>
int DoublyLinkedList<T>::position(){
  return current->index;
}

template <typename T>
DoubleNode<T> DoublyLinkedList<T>::getptr(){
  return *current;
}

template <typename T>
DoubleNode<T> DoublyLinkedList<T>::getptr(int query_index){
  go_to_head();

  while(has_next())
    if(current->index == query_index) return *current;

  go_to_head();
}

template <typename T>
void DoublyLinkedList<T>::randomize(){

  srand(time(NULL));

  DoubleNode<T> *node_list[list_length];
  DoubleNode<T> *randomized_node_list[list_length];


  int index = 0;

  std::unordered_map<int, int> randomized_indexes;

  while(randomized_indexes.size() != list_length){
    randomized_indexes[index] = rand()%list_length;
    index++;
  }

  for(int i=0; i<list_length; i++){
    node_list[i] = current;
    current = current->next;
  }

  index = 0;
  for(auto const &pair : randomized_indexes){

    int to_node_index = pair.first;
    randomized_node_list[index] = node_list[to_node_index];
    index++;
  }

  go_to_head();
  for(int i=0; i<list_length; i++){
    current->random = randomized_node_list[i];
    current = current->next;
  }
  go_to_head();


  return;
}

template <typename T>
void DoublyLinkedList<T>::copy(DoubleNode<T> *from, DoubleNode<T> *to){
  to->data = from->data;
  to->random = from->random;
  to->index = from->index;
  to->prev = from->prev;
  to->next = from->next;

  delete from;
}

template <typename T>
void DoublyLinkedList<T>::print(){
  go_to_head();

  while(current != nullptr){
    std::cout<<"Node: "<<current->index<<" with data: "<<current->data<<" and random node: "<<current->random->index<<std::endl;
    get_next();
  }
  go_to_head();
}

template <typename T>
bool DoublyLinkedList<T>::has_next(){
  return current->next != nullptr;
}

template <typename T>
bool DoublyLinkedList<T>::has_previous(){
  return current->prev != nullptr;
}

template <typename T>
void DoublyLinkedList<T>::get_next(){
  current = current->next;
}

template <typename T>
void DoublyLinkedList<T>::get_previous(){
  current = current->prev;
}

template <typename T>
void DoublyLinkedList<T>::go_to_head(){
  if(head != nullptr) current = head;
  else current = nullptr;
}

template <typename T>
void DoublyLinkedList<T>::go_to_end(){
  while(has_next()) current = current->next;
}

#endif
