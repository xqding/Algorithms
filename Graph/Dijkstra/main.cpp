#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "Heap.h"


int main(int argc, char* argv[])
{
  // open the graph file
  std::ifstream in_file;
  in_file.open(argv[1]);
  if (in_file.fail()) {
    std::cout << "Open file failed: " << argv[1] << std::endl;
    return 1;
  }

  // read the graph
  std::string line;
  std::stringstream ss;
  std::map< int, std::map<int,int> > graph;
  int i,j,d;
  while (std::getline(in_file,line))
  {
    ss.clear();
    ss.str(line);
    ss >> i;
    while (ss)
    {
      ss >> j;
      ss.ignore(1,',');
      ss >> d;
      graph[i][j] = d;
    }
  }

  // Dijkstra Algorithm
  std::map<int, int> min_dist;
  min_dist[1] = 0;
  
  Heap <int> myHeap;
  for(std::map<int,int>::iterator it = graph[1].begin(); it != graph[1].end(); it++)
  {
    std::pair<int,int> tmp (1,it->first);
    myHeap.insert(it->second, tmp) ;
  }

  int num_of_nodes = 200;
  while (myHeap.get_size() > 0)
  {
    std::pair<std::pair<int,int>,int > r = myHeap.extract_min();
    int tail = r.first.first;
    int head = r.first.second;
    int w = r.second;
    std::cout << "tail:" << tail << ",head:" << head << std::endl;
    min_dist[head] = w;
    myHeap.delete_node(head);
    for(std::map<int,int>::iterator it = graph[head].begin(); it != graph[head].end(); it++)
    {
      if (min_dist.count(it->first) == 0)
      {
	std::pair<int, int> tmp (head, it->first);
	myHeap.insert(min_dist[head]+it->second, tmp);
      }
    }
  }
  std::cout << "size: " << min_dist.size() << std::endl;

  for(int i = 1; i <= num_of_nodes; i++)
  {
    std::cout << "Node: " << i << ",distance: " << min_dist[i] << std::endl;
  }

  int v[]  = {7,37,59,82,99,115,133,165,188,197};
  for(int i = 0; i < 10; i++)
  {
    std::cout << min_dist[v[i]] << ",";
  }  
  return 0;
}
