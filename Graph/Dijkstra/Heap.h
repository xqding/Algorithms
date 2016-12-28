/* @(#)Heap.h
 */

#ifndef _HEAP_H
#define _HEAP_H 1
#include <vector>
#include <utility>
#include <map>
#include <set>

template <class T>
class Heap
{
 private:
  int size;
  std::vector < T > weights;
  std::vector < std::pair <int, int> > edges;
  std::map < int, std::set<int> > node_pos_map;
  int left_child(int i);
  int right_child(int i);
  int parent(int i);
 public:
  Heap() { size = 0; };
  void insert(T k, std::pair <int,int> n);
  std::pair <std::pair<int,int>, T> pop(int i);
  void heapify_up(int i);
  void heapify_down(int j);
  std::pair<std::pair<int,int>, T> extract_min();
  void delete_node(int n);
  std::vector <T>& get_weights();
  int get_size();
};

#include "Heap.inl"
#endif /* _HEAP_H */

