#include "linked_list.h"
#include <iostream>
#include <vector>

Node<int>* SortedMerge(Node<int>* a, Node<int>* b){
  Node<int>* result_list = nullptr;

  if(a == nullptr) return (b);
  if(b == nullptr) return (a);

  if(a->data <= b->data){
    result_list = a;
    result_list->next_node = SortedMerge(a->next_node, b);
  }
  else{
    result_list = b;
    result_list->next_node = SortedMerge(a, b->next_node);
  }

  return result_list;
}

Node<int>* mergeKLists(Node<int>* list_array[], int last){
  while(last != 0){
    int i=0, j = last;

    while(i < j){
      list_array[i] = SortedMerge(list_array[i], list_array[j]);

      i++, j--;

      if (i >= j) last = j;
    }
  }

  return list_array[0];
}

void printList(Node<int>* node){
  while(node != nullptr){
    std::cout<<node->data<<std::endl;
    node = node->next_node;
  }
}

int main(){

  std::vector<std::vector<int>> array_of_arrays = {
    {1, 5, 7, 10, 15, 20, 27, 30, 35, 39},
    {2, 4, 6, 21, 23, 25, 34, 36, 37, 40},
    {3, 3, 7, 12, 16, 17, 18, 26, 33, 34}
  };

  int k = array_of_arrays.size();

  Node<int> *node_array[2];

  for(int i=0; i<k; i++){
    std::vector<int> data_list = array_of_arrays[i];

    Node<int>* head = nullptr;
    Node<int>*tail = nullptr;

    for(auto const &new_data : data_list){
      Node<int> *temp = new Node<int>;

      temp->data=new_data;
      temp->next_node=nullptr;
      if(head == nullptr)
      {
        head=temp;
        tail=temp;
        temp=nullptr;
      }
      else
      {
        tail->next_node=temp;
        tail=temp;
      }
    }

    node_array[i] = head;

  }

  Node<int>* head = mergeKLists(node_array, k-1);

  printList(head);

  return 0;

}
