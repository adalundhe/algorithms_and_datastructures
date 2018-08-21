#include "segment_tree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

int get_mid(int start, int end){
  return start + (end - start)/2;
}

int range_minimum_query_util(SegmentTree<int> segment_tree, int segment_start, int segment_end, int query_start, int query_end, int index){

  if(query_start <= segment_start && query_end >= segment_end){
    return segment_tree.at(index);
  }


  if(segment_end < query_start || segment_start > query_end)
    return INT_MAX;

  int mid = get_mid(segment_start, segment_end);

  return std::min(
    range_minimum_query_util(segment_tree, segment_start, mid, query_start, query_end, 2*index+1),
    range_minimum_query_util(segment_tree, mid+1, segment_end, query_start, query_end, 2*index+2)
  );

}

int range_minimum_query(SegmentTree<int> segment_tree, int max_size, int query_start, int query_end){

  if(query_start < 0 || query_end > max_size-1 || query_start > query_end)
    return -1;

  return range_minimum_query_util(segment_tree, 0, max_size-1, query_start, query_end, 0);

}

int main(){
  std::vector<int> a = {1, 3, 2, 7, 9, 11};
  int size = a.size();

  SegmentTree<int> segment_tree(a);

  int query_start = 1;
  int query_end = 5;

  int result = range_minimum_query(segment_tree, size, query_start, query_end);

  std::cout<<result<<std::endl;

  return 0;
}
