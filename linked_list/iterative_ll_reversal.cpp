#include <iostream>
using namespace std;

template <typename T>
struct Node{
	T data;
	Node<T>* next;
};

template <typename T>
Node<T>* reverse(Node<T>* root){

	Node<T>* current = root;
	Node<T>* previous = nullptr;
	Node<T>* next = nullptr;

	while(current != nullptr){
	    next = current->next;
	    current->next = previous;
	    previous=current;
	    current=next;
	}

	root=previous;
	return root;

}

template <typename T>
Node<T>* new_node(T new_data){
	Node<T>* node = new Node<T>;
	node->data = new_data;
	node->next=nullptr;

	return node;
}

int main() {

	Node<int>* root = new_node(1);
	root->next = new_node(2);
	root->next->next = new_node(3);

	root = reverse(root);

	Node<int>* current = root;

	while(current != nullptr){
	    std::cout<<current->data<<std::endl;
	    current = current->next;
	}


	return 0;
}
