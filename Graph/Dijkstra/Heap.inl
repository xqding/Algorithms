#include <iostream>
#include <utility>
#include "Heap.h"

template <class T>
int Heap<T>::left_child(int i)
{
  return 2*i + 1;
}

template <class T>
int Heap<T>::right_child(int i)
{
  return 2*i + 2;
}

template <class T>
int Heap<T>::parent(int i)
{
  return (i+1)/2-1;
}

template <class T>
void Heap< T >::insert(T k, std::pair<int,int> n)
{
  weights.push_back(k);
  size += 1;
  edges.push_back(n);
  node_pos_map[n.second].insert(size-1);
  heapify_up(size-1);
}

template <class T>
std::pair<std::pair<int,int>, T> Heap<T>::extract_min()
{
  T k = weights[0];
  std::pair <int,int> n = edges[0];
  std::pair <std::pair<int,int>, T> res(n, k);

  node_pos_map[n.second].erase(0);
  node_pos_map[edges[size-1].second].erase(size-1);
  
  weights[0] = weights[size-1];
  edges[0] = edges[size-1];
  weights.pop_back();
  edges.pop_back();
  size = weights.size();
  node_pos_map[edges[0].second].insert(0);
  
  heapify_down(0);
  return res;
}

template <class T>
void Heap<T>::delete_node(int n)
{
  while(node_pos_map[n].size() > 0)
  {
    std::cout << n << "," << *node_pos_map[n].begin() << "," << size << std::endl;
    pop(*node_pos_map[n].begin());
  }
}

template <class T>
std::pair <std::pair<int,int>, T> Heap<T>::pop(int i)
{
  std::pair <int,int> n = edges[i];
  int k = weights[i];
  std::pair<std::pair <int,int>,T> res(n,k);
  
  if (i < size - 1)
  {
    node_pos_map[edges[i].second].erase(i);
    node_pos_map[edges[size-1].second].erase(size-1);
    node_pos_map[edges[size-1].second].insert(i);  
    weights[i] = weights[size-1];
    edges[i] = edges[size-1];
    weights.pop_back();
    edges.pop_back();
    size = weights.size();
    heapify_down(i);
  }
  else if (i == size - 1)
  {
    node_pos_map[edges[i].second].erase(i);
    weights.pop_back();
    edges.pop_back();
    size = weights.size();
  }
  return res;
}

template <class T>
void Heap<T>::heapify_up(int i)
{  
  int p = parent(i);
  if (p >= 0 && weights[p] > weights[i])
  {
    // swap key
    T tmp = weights[p];
    weights[p] = weights[i];
    weights[i] = tmp;

    // change the node idx to position map
    node_pos_map[edges[p].second].erase(p);
    node_pos_map[edges[i].second].erase(i);
    node_pos_map[edges[p].second].insert(i);
    node_pos_map[edges[i].second].insert(p);
            
    // swap node idx
    std::pair<int,int> tmp_node = edges[p];
    edges[p] = edges[i];
    edges[i] = tmp_node;
    heapify_up(p);
  }
}

template <class T>
void Heap<T>::heapify_down(int i)
{
  int left = left_child(i);
  int right = left + 1;
  int min_idx = i;
  if ( left < size && weights[left] < weights[min_idx])
  {
    min_idx = left;
  }
  if (right < size && weights[right] < weights[min_idx])
  {
    min_idx = right;
  }
  // if the ids witht the mumum key is not the current key
  if (min_idx != i)
  {
    // swap key
    T tmp = weights[min_idx];
    weights[min_idx] = weights[i];
    weights[i] = tmp;

    // change the node idx to position map
    node_pos_map[edges[min_idx].second].erase(min_idx);
    node_pos_map[edges[i].second].erase(i);
    node_pos_map[edges[min_idx].second].insert(i);
    node_pos_map[edges[i].second].insert(min_idx);
            
    // swap node idx
    std::pair <int, int> tmp_node = edges[min_idx];
    edges[min_idx] = edges[i];
    edges[i] = tmp_node;
    heapify_down(min_idx);
  }
}

template <class T>
std::vector<T>& Heap<T>::get_weights()
{
  return weights;
}

template <class T>
int Heap<T>::get_size()
{
  return size;
}

template <class T>
std::ostream& operator<<(std::ostream &os, Heap<T> hp)
{
  for(int i = 0; i < hp.get_size(); i++)
  {
    os << hp.get_weights()[i] << ",";
  }
  return os;
}
