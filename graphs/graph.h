#ifndef __GRAPH_H_INCLUDES__
#define __GRAPH_H_INCLUDES__

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>

template <typename T>
struct Node{
  T data;
  unsigned id;
};

template <typename T>
class Graph{
  public:
    Graph();
    Graph(unsigned V);
    void clear();
    void insert_node(unsigned id);
    void insert_node(Node<T> new_node);
    void add_directed_edge(unsigned from_id, unsigned to_id, int weight);
    void add_undirected_edge(unsigned from_id, unsigned to_id, int weight);
    bool has_directed_edge(unsigned from_id, unsigned to_id);
    bool has_undirected_edge(unsigned from_id, unsigned to_id);
    std::vector<unsigned> DFS(unsigned start_id);
    std::vector<unsigned> BFS(unsigned start_id);
    void print_matrix();
    unsigned find_min_edge();
    std::map<unsigned, std::pair<unsigned, unsigned>> sort_edges();
    void delete_directed_edge(unsigned from_id, unsigned to_id);
    void delete_undirected_edge(unsigned from_id, unsigned to_id);
    unsigned nodes_size();
    unsigned edges_size();
    int get_edge_weight(unsigned from_id, unsigned to_id);
  private:
    std::map<unsigned, std::pair<unsigned, unsigned>> edges;
    std::unordered_map<unsigned, std::vector<unsigned>> adjacency_list;
    int *adjacency_matrix;
    unsigned number_of_nodes = 0;
    unsigned number_of_edges = 0;
    void resize_matrix();
    std::vector<unsigned> get_neighbors(unsigned id);
    unsigned get_node_degree(unsigned id);
};

template <typename T>
Graph<T>::Graph(){}

template <typename T>
Graph<T>::Graph(unsigned V){

  int new_adjacency_matrix[V * V];

  for(unsigned i=0; i<(V * V); ++i){
    new_adjacency_matrix[i] = 0;
  }

  adjacency_matrix = new_adjacency_matrix;

  for(unsigned index=0; index<V; ++index)
    insert_node(index);

}

template <typename T>
void Graph<T>::insert_node(unsigned id){

  Node<T> new_node;
  new_node.data = T();
  new_node.id = id;

  std::vector<unsigned> neighbors = {};

  std::pair<unsigned, std::vector<unsigned>> node_and_neighbors(new_node.id, neighbors);
  adjacency_list.insert(node_and_neighbors);

  resize_matrix();

}

template <typename T>
void Graph<T>::insert_node(Node<T> new_node){

  std::vector<unsigned> neighbors = {};

  std::pair<unsigned, std::vector<unsigned>> node_and_neighbors(new_node.id, neighbors);
  adjacency_list.insert(node_and_neighbors);

  resize_matrix();

}

template <typename T>
void Graph<T>::add_directed_edge(unsigned from_id, unsigned to_id, int weight){

  if(from_id < 0 || from_id > number_of_nodes) return;
  if(to_id < 0 || to_id > number_of_nodes) return;

  adjacency_list[from_id].push_back(to_id);

  unsigned insert_index = from_id * number_of_nodes + to_id;

  adjacency_matrix[from_id * number_of_nodes + to_id] = weight;

  std::pair<unsigned, unsigned> nodes(from_id, to_id);
  edges[weight] = nodes;

  number_of_edges++;

}

template <typename T>
void Graph<T>::add_undirected_edge(unsigned from_id, unsigned to_id, int weight){

  if(from_id < 0 || from_id > number_of_nodes) return;
  if(to_id < 0 || to_id > number_of_nodes) return;

  adjacency_list[from_id].push_back(to_id);
  adjacency_list[to_id].push_back(from_id);

  unsigned insert_index = from_id * number_of_nodes + to_id;

  adjacency_matrix[from_id * number_of_nodes + to_id] = weight;
  adjacency_matrix[to_id * number_of_nodes + from_id] = weight;

  std::pair<unsigned, unsigned> nodes(from_id, to_id);
  edges[weight] = nodes;

  number_of_edges++;

}

template <typename T>
bool Graph<T>::has_directed_edge(unsigned from_id, unsigned to_id){
  return adjacency_matrix[from_id * number_of_nodes + to_id] != 0;
}

template <typename T>
bool Graph<T>::has_undirected_edge(unsigned from_id, unsigned to_id){
  return adjacency_matrix[from_id * number_of_nodes + to_id] != 0 && adjacency_matrix[to_id * number_of_nodes + from_id] != 0;
}

template <typename T>
std::vector<unsigned> Graph<T>::DFS(unsigned start_id){

  std::vector<bool> visited(number_of_nodes, false);
  std::vector<unsigned> stack;
  std::vector<unsigned> visited_nodes(number_of_nodes);

  stack.push_back(start_id);

  while(!stack.empty()){

    unsigned selected_node = stack.back();
    stack.pop_back();

    if(!visited.at(selected_node)){
      visited.at(selected_node) = true;
      visited_nodes.push_back(selected_node);
    }

    std::vector<unsigned> neighbors = get_neighbors(selected_node);

    for(auto const &neighbor : neighbors)
      if(!visited.at(neighbor))
        stack.push_back(neighbor);

  }

  return visited_nodes;

}

template <typename T>
std::vector<unsigned> Graph<T>::BFS(unsigned start_id){

  std::vector<bool> visited(number_of_nodes, false);
  std::list<unsigned> queue;
  std::vector<unsigned> visited_nodes(number_of_nodes);

  queue.push_back(start_id);

  while(!queue.empty()){

    unsigned selected_node = queue.front();
    queue.pop_front();

    if(!visited.at(selected_node)){
      visited.at(selected_node) = true;
      visited_nodes.push_back(selected_node);
    }

    std::vector<unsigned> neighbors = get_neighbors(selected_node);

    for(auto const &neighbor : neighbors)
      if(!visited.at(neighbor))
        queue.push_back(neighbor);

  }

  return visited_nodes;

}


template <typename T>
void Graph<T>::resize_matrix(){

  unsigned previous_size = number_of_nodes * number_of_nodes;
  number_of_nodes++;
  unsigned current_size = number_of_nodes * number_of_nodes;

  int new_adjacency_matrix[current_size * current_size];

  for(int i=0; i<(current_size* current_size); ++i)
    new_adjacency_matrix[i] = 0;

  for(unsigned index=0; index<number_of_nodes; ++index)
    for(unsigned index_j=0; index_j<number_of_nodes; ++index_j)
      new_adjacency_matrix[index * previous_size + index_j] = (index < previous_size) ? adjacency_matrix[index] : 0;

  adjacency_matrix = new_adjacency_matrix;

}

template <typename T>
std::vector<unsigned> Graph<T>::get_neighbors(unsigned id){
  std::vector<unsigned> neighbors = adjacency_list[id];
  std::vector<unsigned> neighbors_found(neighbors);

  neighbors_found.erase(neighbors_found.begin());

  return neighbors_found;

}

template <typename T>
void Graph<T>::print_matrix(){

  for(unsigned i=0; i<number_of_nodes; ++i){
    for(unsigned j=0; j<number_of_nodes; ++j)
      std::cout<<adjacency_matrix[i * number_of_nodes + j]<<" ";
    std::cout<<std::endl;
  }

}


template <typename T>
std::map<unsigned, std::pair<unsigned, unsigned>> Graph<T>::sort_edges(){
  return edges;
}

template <typename T>
void Graph<T>::delete_directed_edge(unsigned from_id, unsigned to_id){
  std::remove_copy(adjacency_list[from_id].begin(),adjacency_list[from_id].end(), adjacency_list[from_id].begin(), to_id);

  adjacency_matrix[from_id * number_of_nodes + to_id] = 0;
  number_of_edges--;
}

template <typename T>
void Graph<T>::delete_undirected_edge(unsigned from_id, unsigned to_id){

  std::vector<unsigned> adjacency_list_from(adjacency_list[from_id]);

  std::remove_copy(adjacency_list[from_id].begin(),adjacency_list[from_id].end(), adjacency_list[from_id].begin(), to_id);
  std::remove_copy(adjacency_list[to_id].begin(),adjacency_list[to_id].end(), adjacency_list[to_id].begin(), from_id);

  // adjacency_list_from.erase(adjacency_list_from.begin() + to_id);
  // adjacency_list[to_id].erase(adjacency_list[to_id].begin() + from_id);

  adjacency_matrix[from_id * number_of_nodes + to_id] = 0;
  adjacency_matrix[to_id * number_of_nodes + from_id] = 0;
  number_of_edges--;
}

template <typename T>
unsigned Graph<T>::nodes_size(){
  return number_of_nodes;
}

template <typename T>
unsigned Graph<T>::edges_size(){
  return number_of_edges;
}

template <typename T>
int Graph<T>::get_edge_weight(unsigned from_id, unsigned to_id){
  return adjacency_matrix[from_id * number_of_nodes + to_id];
}

template <typename T>
unsigned Graph<T>::get_node_degree(unsigned id){

}

#endif
