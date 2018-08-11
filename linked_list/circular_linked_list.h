#ifndef __CIRCULAR_LINKED_LIST_H_INCLUDED__
#define __CIRCULAR_LINKED_LIST_H_INCLUDED__

#include "linked_list.h"
#include <iostream>
#include <vector>

template <typename T>
class CircularLinkedList{
  public:
    CircularLinkedList();
    CircularLinkedList(T node_data);
    CircularLinkedList(std::vector<T> node_data);
    void append(T node_data);
    void append(std::vector<T> node_data);
    void advance();
    void tohead();
    void toend();
    bool isend();
    T data();
    int position();
    int length();
  private:
    int pos = 0;
    int start_position = 0;
    int end_position = 0;
    int list_length = 0;
    Node<T> *head = nullptr, *current = nullptr, *tail = nullptr;
    void go_to_head();
    bool has_next();
    void get_next();
    void go_to_end();
};

template <typename T>
CircularLinkedList<T>::CircularLinkedList(){}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(T node_data){
  append(node_data);
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(std::vector<T> node_data){
  append(node_data);
}

template <typename T>
void CircularLinkedList<T>::append(T node_data){
  Node<T> *temp = new Node<T>;
  temp->data=node_data;
  temp->index = list_length;
  temp->next_node=nullptr;
  if(head == nullptr)
  {
    head=temp;
    current=temp;
    tail=temp;
    temp->next_node = temp;
  }
  else
  {
    temp->next_node=tail->next_node;
    tail->next_node = temp;
    tail=temp;
  }

  list_length++;
  end_position = list_length;
}

template <typename T>
void CircularLinkedList<T>::append(std::vector<T> node_data){
  for(auto const &data : node_data) append(data);
}

template <typename T>
void CircularLinkedList<T>::tohead(){
  go_to_head();
}

template <typename T>
void CircularLinkedList<T>::advance(){
  get_next();
}

template <typename T>
void CircularLinkedList<T>::toend(){
  go_to_end();
}

template <typename T>
bool CircularLinkedList<T>::isend(){
  return pos == end_position-1;
}

template <typename T>
T CircularLinkedList<T>::data(){
  return current->data;
}

template <typename T>
int CircularLinkedList<T>::position(){
  return current->index;
}

template <typename T>
void CircularLinkedList<T>::go_to_head(){
  if(pos == 0) current = head;
  else current = nullptr;
}

template <typename T>
void CircularLinkedList<T>::get_next(){
  current = current->next_node;
  pos += 1;
}

template <typename T>
void CircularLinkedList<T>::go_to_end(){
  while(has_next()) current = current->next_node;
}

template <typename T>
bool CircularLinkedList<T>::has_next(){
  return pos < end_position;
}


#endif
