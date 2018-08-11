#ifndef __UNION_FIND_H_INCLUDES__
#define __UNION_FIND_H_INCLUDES__

#include <unordered_map>
#include <iostream>
#include <vector>
#include "graph.h"

template <typename T>
class UnionFind{
public:
  UnionFind();
  UnionFind(unsigned V);
  void add_directed_edge(unsigned from_id, unsigned to_id, int weight);
  void add_undirected_edge(unsigned from_id, unsigned to_id, int weight);
  void insert_node(unsigned id);
  void insert_node(Node<T> new_node);
  unsigned find(unsigned id);
  bool connected(unsigned from_id, unsigned to_id);
  void _union(unsigned from_id, unsigned to_id);
  void _union(unsigned from_id, unsigned to_id, int weight);
  void print_matrix();
  void delete_directed_edge(unsigned from_id, unsigned to_id);
  void delete_undirected_edge(unsigned from_id, unsigned to_id);
  unsigned nodes_size();
  unsigned edges_size();
  int get_edge_weight(unsigned from_id, unsigned to);
  std::vector<int> get_compressed_tree();
  // void union(std::vector<unsigned> parent, unsigned node_one, unsigned node_two);

private:
  std::unordered_map<unsigned, unsigned> node_sets;
  std::vector<int> compressed_path_tree;
  Graph<T> graph;
  unsigned number_of_sets = 0;
  void assign_sets(unsigned from_id, unsigned to_id);
  void compress_paths();
  unsigned count = 0;
};


template <typename T>
UnionFind<T>::UnionFind(){}

template <typename T>
UnionFind<T>::UnionFind(unsigned V){

  count = V;

  for(unsigned i=0; i<V-1; ++i){
      graph.insert_node(i);
      compressed_path_tree.push_back(i);
  }
}

template <typename T>
void UnionFind<T>::add_directed_edge(unsigned from_id, unsigned to_id, int weight){
  graph.add_directed_edge(from_id, to_id, weight);
  assign_sets(from_id, to_id);
}

template <typename T>
void UnionFind<T>::add_undirected_edge(unsigned from_id, unsigned to_id, int weight){
  graph.add_undirected_edge(from_id, to_id, weight);
  assign_sets(from_id, to_id);
}

template <typename T>
void UnionFind<T>::insert_node(unsigned id){
  graph.insert_node(id);
}

template <typename T>
void UnionFind<T>::insert_node(Node<T> new_node){
  graph.insert_node(new_node);
}

template <typename T>
unsigned UnionFind<T>::find(unsigned id){

  unsigned root = id;

  while(root != compressed_path_tree[root])
    root = compressed_path_tree[root];

  while(id != root){
      unsigned new_id = compressed_path_tree[id];
      compressed_path_tree[id] = root;
      id = new_id;
  }

  return root;
}

template <typename T>
bool UnionFind<T>::connected(unsigned from_id, unsigned to_id){
  return find(from_id) == find(to_id);
}

template <typename T>
void UnionFind<T>::_union(unsigned from_id, unsigned to_id){

  unsigned root_of_from = find(from_id);
  unsigned root_of_to = find(to_id);

  if(root_of_from == root_of_to) return;

  compressed_path_tree[root_of_from] = root_of_to;
  count--;

}

template <typename T>
void UnionFind<T>::_union(unsigned from_id, unsigned to_id, int weight){

  unsigned root_of_from = find(from_id);
  unsigned root_of_to = find(to_id);

  if(root_of_from == root_of_to) return;

  compressed_path_tree[root_of_from] = root_of_to;

  graph.add_undirected_edge(root_of_from, root_of_to, weight);

  count--;

}

template <typename T>
void UnionFind<T>::assign_sets(unsigned from_id, unsigned to_id){
  if(node_sets.find(from_id) == node_sets.end() && node_sets.find(to_id) == node_sets.end()){
    // If we have seen neither of these nodes before, is a new set...
    number_of_sets++;
    node_sets[from_id] = number_of_sets;
    node_sets[to_id] = number_of_sets;

    compressed_path_tree[to_id] = from_id;
    compressed_path_tree[from_id] = from_id;

  }
  else if(node_sets.find(from_id) == node_sets.end()){
    //else if we haven't seen the from node before...
    node_sets[from_id] = node_sets[to_id];
    compressed_path_tree[from_id] = to_id;
  }
  else if(node_sets.find(to_id) == node_sets.end()){
    //we haven't seen the to node before...
    node_sets[to_id] = node_sets[from_id];
    compressed_path_tree[to_id] = from_id;
  }

}

template <typename T>
void UnionFind<T>::print_matrix(){
  graph.print_matrix();
}

template <typename T>
void UnionFind<T>::delete_directed_edge(unsigned from_id, unsigned to_id){
  graph.delete_directed_edge(from_id, to_id);
}

template <typename T>
void UnionFind<T>::delete_undirected_edge(unsigned from_id, unsigned to_id){
  graph.delete_undirected_edge(from_id, to_id);
}

template <typename T>
unsigned UnionFind<T>::nodes_size(){
  return graph.nodes_size();
}

template <typename T>
int UnionFind<T>::get_edge_weight(unsigned from_id, unsigned to_id){
  return graph.get_edge_weight(from_id, to_id);
}


template <typename T>
unsigned UnionFind<T>::edges_size(){
  return graph.edges_size();
}

template <typename T>
std::vector<int> UnionFind<T>::get_compressed_tree(){
  return compressed_path_tree;
}

#endif
