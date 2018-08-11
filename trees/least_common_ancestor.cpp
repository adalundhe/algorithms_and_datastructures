#include <map>
#include <vector>
#include <iostream>
#include "binary_tree.h"


int find_lca(BinaryTree<int> tree, int node_a, int node_b){

  unsigned tree_size = tree.size();
  unsigned current_node = 0;

  while(current_node < tree_size){
    if(tree.at(current_node) > tree.at(node_a) && tree.at(current_node) > tree.at(node_b))
      current_node = tree.leftchild(current_node);
    else if (tree.at(current_node) < tree.at(node_a) && tree.at(current_node) < tree.at(node_b))
      current_node = tree.rightchild(current_node);

    else break;
  }

  return current_node;
}

int main(){

  const std::vector<int> data = {20, 8, 22, 4, 12, 10, 14};

  BinaryTree<int> tree(data);
  std::vector<int> tree_indexes = tree.level_order();

  unsigned node_a = tree.node(10);
  unsigned node_b = tree.node(22);

  int result = find_lca(tree, node_a, node_b);

  std::cout<<"The least common ancestor of nodes "<<tree.at(node_a)<<" and "<<tree.at(node_b)<<" is node: "<<tree.at(result)<<std::endl;

  return 0;
}
