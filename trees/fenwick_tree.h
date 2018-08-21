#ifndef __FENWICK_TREE_H_INCLUDES__
#define __FENWICK_TREE_H_INCLUDES__
#include <vector>

template <typename T>
class FenwickTree{
  public:
    FenwickTree(std::vector<T> data);
    void update(int index, T data);
    T query(int index);
  private:
    std::vector<T> tree;
    int size=0;
};

template <typename T>
FenwickTree<T>::FenwickTree(std::vector<T> data){

  size = data.size();
  tree.resize(size + 1);

  for(unsigned i=1; i<= size; ++i)
    tree.at(i) = 0;

  for(int i=0; i<size; ++i)
    update(i, data.at(i));
}

template <typename T>
void FenwickTree<T>::update(int index, T value){

  index++;

  while(index <= size){
    tree.at(index) += value;
    index += index & (-index);
  }

}

template <typename T>
T FenwickTree<T>::query(int index){

  int sum = 0;
  index++;

  while(index>0){
    sum += tree.at(index);
    index -= index & (-index);
  }

  return sum;
}

#endif
