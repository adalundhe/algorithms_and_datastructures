#ifndef __SEGMENT_TREE_H_INCLUDES__
#define __SEGMENT_TREE_H_INCLUDES__
#include <stdlib.h>
#include <limits.h>
#include <vector>

template <typename T>
class SegmentTree{
  public:
    SegmentTree(std::vector<T> new_data);
    void update(int idx, T value);
    T at(int idx);
    T query(int from, int to);
  private:
    std::vector<T> data;
    long long int max_size = 1000000;
    long long int size=0;

};


template <typename T>
SegmentTree<T>::SegmentTree(std::vector<T> new_data){

  size = new_data.size();

  data.resize(2 * max_size);

  for(unsigned i=0; i<size; ++i)
    data[size+i] = new_data.at(i);

  for(int i=size-1; i>0; --i)
    data[i] = data[i<<1] + data[i<<1 | 1];
}

template <typename T>
void SegmentTree<T>::update(int idx, T value){

  data[idx+size] = value;
  idx = idx+size;

  for(unsigned i=idx; i>1; i >>= 1)
    data[i>>1] = data[i] + data[i^1];
}

template <typename T>
T SegmentTree<T>::at(int idx){
  if(idx > size)
    return data[2*size-1];

  return data[idx+size];

}

template <typename T>
T SegmentTree<T>::query(int from, int to){

  int total = 0;

  for(from += size, to += size; from<to; from >>= 1, to >>= 1){

    if(from&1)
      total += data[from++];
    if(to&1)
      total += data[--to];

  }

  return total;

}

#endif
