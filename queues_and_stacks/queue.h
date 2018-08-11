#ifndef __QUEUE_H_INCLUDED__
#define __QUEUE_H_INCLUDED__

#include <vector>
#include <iostream>
#include <list>

template <typename T>
class Queue{
  public:
    Queue();
    Queue(T new_data);
    Queue(std::vector<T> new_data);
    void enqueue(T new_data);
    T dequeue();
    int length();
  private:
    std::list<T> queue_data;
    int queue_length = 0;
};

template <typename T>
Queue<T>::Queue(){}

template <typename T>
Queue<T>::Queue(T new_data){
  enqueue(new_data);
}

template <typename T>
Queue<T>::Queue(std::vector<T> new_data){
  for(auto const &data_item : new_data) enqueue(data_item);
}

template <typename T>
void Queue<T>::enqueue(T new_data){
  queue_data.push_back(new_data);
  queue_length++;
}

template <typename T>
T Queue<T>::dequeue(){
  T data_item = queue_data.front();
  queue_data.pop_front();
  queue_length--;

  return data_item;
}

template <typename T>
int Queue<T>::length(){
  return queue_length;
}

#endif
