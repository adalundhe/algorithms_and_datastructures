#include <iostream>
#include <stack>
#include <unordered_map>
#include <limits.h>

template <typename T>
struct Node{
  T data;
  Node *left, * right;
};

template <typename T>
Node<T>* create_node(T data){
  Node<T>* new_node = new Node<T>;
  new_node->data = data;
  new_node->left = nullptr;
  new_node->right = nullptr;

  return new_node;
}

template <typename T>
T maxPathSum2(Node<T> *root) {
        if (root == NULL) return 0;
        int global_max = INT_MIN;
        std::stack<Node<T>*> traverse;
        traverse.push(root);
        while(!traverse.empty()) {
            Node<T>* p = traverse.top();
            global_max = global_max > p->data ? global_max : p->data;
            traverse.pop();
            if (p->right) {
                traverse.push(p->right);
                p->right->data += p->data;
            }
            if (p->left) {
                traverse.push(p->left);
                p->left->data += p->data;
            }
        }
        return global_max;
  }

int main(){

  Node<int>* root = create_node(-4);
  root->left = create_node(2);
  root->right = create_node(6);
  root->left->left = create_node(-5);
  root->left->right = create_node(2);
  root->right->left = create_node(1);
  root->right->right = create_node(5);

  int max_sum = maxPathSum2<int>(root);

  std::cout<<"Result: "<<max_sum<<std::endl;

  return 0;
}
