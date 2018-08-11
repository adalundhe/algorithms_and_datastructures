#include "doubly_linked_list.h"
#include <iostream>
#include <vector>

DoublyLinkedList<int> clone(DoublyLinkedList<int> list){
  DoublyLinkedList<int> dll_copy;
  DoubleNode<int> *current = new DoubleNode<int>;
  DoubleNode<int> *temp;

  int length = list.length();
  int start = list.position();
  int pos = 0;

  while(pos < length){
    DoubleNode<int> head = list.getptr();
    list.copy(&head, current);

    int insert_index = pos + 1;
    list.insert(current, insert_index);
    pos++;

  }
  delete current;

  int new_length = list.length() * 2;
  pos = start + 1;

  while(!list.isend()){
    DoubleNode<int> head = list.getptr();
    list.copy(&head, current);

    current->next->random = current->random->next;

    list.overwrite(current, pos);

    pos += current->next ? 2 : 1;
    list.advance();

    if(current->next){
      list.advance();
    }

  }

  list.tohead();

  DoubleNode<int> original = list.getptr();
  DoubleNode<int> *copy;
  list.copy(&original, current);

  temp = current->next;
  temp = copy;

  while(current != nullptr && copy != nullptr){

    current->next = current->next ? current->next->next : current->next;
    copy->next = copy->next ? copy->next->next : copy->next;

    current = current->next;
    copy = copy->next;
  }

  pos = start;
  while(temp != nullptr){
    dll_copy.insert(temp, pos);
    temp = temp->next;
    pos++;
  }

  dll_copy.reset();

  dll_copy.tohead();

  std::cout<<"\nNEW LIST\n"<<std::endl;

  dll_copy.print();

  delete temp;

  return dll_copy;
}

int main(){
  std::vector<int> data;

  for(int i=1; i<=100000; i++) data.push_back(i);

  DoublyLinkedList<int> dll(data);
  DoublyLinkedList<int> new_list;

  dll.randomize();

  new_list = clone(dll);

  dll.clear();
  // new_list.clear();

  return 0;
}
