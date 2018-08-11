#include "graph.h"
#include "union_find.h"
#include <vector>
#include <map>

void KruskalMST(UnionFind<int> union_find, std::map<unsigned, std::pair<unsigned, unsigned>> sorted){

  unsigned V = union_find.nodes_size();
  unsigned edges = 0;
  unsigned i = 0;

  for(auto const &edge : sorted){

    std::pair<unsigned, unsigned> nodes = edge.second;
    int weight = edge.first;

    unsigned node_a = union_find.find(nodes.first);
    unsigned node_b = union_find.find(nodes.second);
    if(node_a != node_b){
      union_find.add_undirected_edge(node_a, node_b, weight);
      edges++;

    }


  }

  std::cout<<"\nMinimum spanning tree matrix:"<<std::endl;
  union_find.print_matrix();

}


int main(){

  Graph<int> graph(5);



  // graph.DFS(0);

  graph.add_undirected_edge(0, 1, 10);
  graph.add_undirected_edge(0, 2, 6);
  graph.add_undirected_edge(0, 3, 5);
  graph.add_undirected_edge(1, 3, 15);
  graph.add_undirected_edge(2, 3, 4);

  graph.print_matrix();

  std::map<unsigned, std::pair<unsigned, unsigned>> sorted = graph.sort_edges();

  // graph.BFS(2);
  //
  // unsigned N = 6;
  //
  UnionFind<int> union_find(5);

  graph.add_undirected_edge(0, 1, 10);
  graph.add_undirected_edge(0, 2, 6);
  graph.add_undirected_edge(0, 3, 5);
  graph.add_undirected_edge(1, 3, 15);
  graph.add_undirected_edge(2, 3, 4);

  KruskalMST(union_find, sorted);

  //
  // union_find.print_matrix();
  //
  // std::cout<<"Graph "<<((union_find.connected(0, 4) ? "has a cycle." : "does not have a cycle."))<<std::endl;

  // for(unsigned i=0; i<5; ++i)
  //   for(unsigned j=0; j<5; ++j)
  //     std::cout<<"Node: "<<i<<" is: "<<((union_find.connected(i, j) ? "connected" : "not connected"))<<" to node: "<<j<<std::endl;

  // std::cout<<union_find.connected(0, 1);

  return 0;
}
