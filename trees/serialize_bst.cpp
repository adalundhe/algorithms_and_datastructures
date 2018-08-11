#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "binary_tree.h"

void serialize(BinaryTree<int> tree){

  FILE* serialized_bst = fopen("serialized_bst.txt", "w");


  std::vector<int> nodes = tree.level_order();

  for(auto const &node : nodes){
    fprintf(serialized_bst, "%d\n",tree.at(node));
  }

  fclose(serialized_bst);

}

BinaryTree<int> deserialize(const char* file_name, unsigned tree_size){

  BinaryTree<int> deserialized_tree;

  FILE* serialized_bst = fopen(file_name, "r");

  std::string::size_type sz;

  char ch = getc(serialized_bst);
  std::string node = "";

  while(ch != EOF){
    if(ch != '\n'){
      int value = ch - '0';
      node += std::to_string(value);
    }
    else{
      int node_value = std::stoi(node, &sz);
      deserialized_tree.insert(node_value);
      node = "";
    }

    ch = getc(serialized_bst);
  }

  fclose(serialized_bst);

  return deserialized_tree;

}

int main(){

  const std::vector<int> data = {20, 8, 22, 4, 12, 10, 14};

  BinaryTree<int> tree(data);
  BinaryTree<int> tree_two;

  serialize(tree);

  tree_two = deserialize("serialized_bst.txt", tree.size());

  std::vector<int> indexes = tree_two.inorder();

  std::cout<<(tree == tree_two)<<std::endl;

  return 0;
}
