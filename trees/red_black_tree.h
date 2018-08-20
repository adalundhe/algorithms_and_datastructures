#ifndef __RED_BLACK_TREE_H_INCLUDES__
#define __RED_BLACK_TREE_H_INCLUDES__
#include <stack>
#include <iostream>

template <typename T>
struct Node{
  T data;
  bool color;
  Node<T> *left = nullptr, *right = nullptr, *parent = nullptr;
};

template <typename T>
class RedBlackTree{
  public:
    RedBlackTree();
    void insert(T data);
    void print();
  private:
    Node<T> *root = nullptr;
    enum Color {RED, BLACK};
    Node<T>* insert_node(Node<T> * __restrict__ node,  Node<T> * __restrict__ new_node);
    void balance_tree(Node<T> *&root, Node<T> *&pt);
    void left_rotate(Node<T> *&root, Node<T> *&node);
    void right_rotate(Node<T> *&root, Node<T> *&node);
    void swap(bool * from, bool * to);
};

template <typename T>
RedBlackTree<T>::RedBlackTree(){};

template <typename T>
void RedBlackTree<T>::insert(T data){
  Node<T> *new_node = new Node<T>;
  new_node->data = data;
  root = insert_node(root, new_node);
  balance_tree(root, new_node);
}

template <typename T>
void RedBlackTree<T>::print(){

  std::stack<Node<T>*> node_stack;
  node_stack.push(root);

  while(!node_stack.empty()){

    Node<T>* current = node_stack.top();
    node_stack.pop();

    std::cout<<"Data: "<<current->data<<std::endl;

    if(current->left != nullptr)
      node_stack.push(current->left);
    if(current->right != nullptr)
      node_stack.push(current->right);

  }

}

template <typename T>
Node<T>* RedBlackTree<T>::insert_node(Node<T> * __restrict__ root, Node<T> * __restrict__ new_node){
  if(root == nullptr)
    return new_node;

  if(new_node->data < root->data){
    root->left = insert_node(root->left, new_node);
    root->left->parent = root;
  }
  else if(new_node->data > root->data){
    root->right = insert_node(root->right, new_node);
    root->right->parent = root;
  }

  return root;

}

template <typename T>
void RedBlackTree<T>::balance_tree(Node<T> *&root, Node<T> *&pt)
{
    Node<T> *parent_pt = nullptr;
    Node<T> *grand_parent_pt = nullptr;

    while ((pt != root) && (pt->color != BLACK) &&
           (pt->parent->color == RED))
    {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left) {

            Node<T> *uncle_pt = grand_parent_pt->right;

            if (uncle_pt != NULL && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }

            else {
                if (pt == parent_pt->right) {
                    left_rotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                right_rotate(root, grand_parent_pt);
                swap(&parent_pt->color, &grand_parent_pt->color);
                pt = parent_pt;
            }
        }

        else
        {
            Node<T> *uncle_pt = grand_parent_pt->left;

            if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else {

                if (pt == parent_pt->left) {
                    right_rotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                left_rotate(root, grand_parent_pt);
                swap(&parent_pt->color, &grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
}

template <typename T>
void RedBlackTree<T>::left_rotate(Node<T> *&root, Node<T> *&node)
{
    Node<T> *pt_right = node->right;

    node->right = pt_right->left;

    if (node->right != NULL)
        node->right->parent = node;

    pt_right->parent = node->parent;

    if (node->parent == NULL)
        root = pt_right;

    else if (node == node->parent->left)
        node->parent->left = pt_right;

    else
        node->parent->right = pt_right;

    pt_right->left = node;
    node->parent = pt_right;
}

template <typename T>
void RedBlackTree<T>::right_rotate(Node<T> *&root, Node<T> *&node)
{
    Node<T> *pt_left = node->left;

    node->left = pt_left->right;

    if (node->left != nullptr)
        node->left->parent = node;

    pt_left->parent = node->parent;

    if (node->parent == nullptr)
        root = pt_left;

    else if (node == node->parent->left)
        node->parent->left = pt_left;

    else
        node->parent->right = pt_left;

    pt_left->right = node;
    node->parent = pt_left;
}

template <typename T>
void RedBlackTree<T>::swap(bool * from, bool * to){
  bool temp = *from;
  *from = *to;
  *to = temp;
}

#endif
