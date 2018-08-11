#include <iostream>
#include <unordered_set>
#include <map>

template <typename T>
struct Node{
  int data;
  Node<T>* next;
};


template <typename T>
void push(Node<T>** head, T new_data){
  Node<T>* new_node = new Node<T>;
  new_node->data = new_data;
  new_node->next = (*head);
  (*head) = new_node;

}

template <typename T>
std::map<T, T> check_for_pair_sum(Node<T>* head, int sum){
  Node<T>* current = head;

  std::unordered_set<T> hash_set;
  std::map<T, T> result;

  while(current != nullptr){

    T current_data = current->data;

    if(hash_set.find(sum - current_data) != hash_set.end()){

      std::pair<T, T> sum_pair(current_data, sum-current_data);
      result.insert(sum_pair);

    }
    hash_set.insert(current->data);
    current = current->next;

  }

  return result;

}

int main(){

  Node<int>* head = nullptr;

  push(&head, 1);
  push(&head, 4);
  push(&head, 1);
  push(&head, 12);
  push(&head, 1);
  push(&head, 18);
  push(&head, 47);
  push(&head, 16);
  push(&head, 12);
  push(&head, 14);
  push(&head, 10);
  push(&head, 8);

  std::map<int, int> result = check_for_pair_sum<int>(head, 26);

  for(auto const &sum_pair : result)
    std::cout<<"Got: "<<sum_pair.first<<" "<<sum_pair.second<<std::endl;

  return 0;
}
