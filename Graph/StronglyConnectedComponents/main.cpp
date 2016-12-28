#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "DFS.h"

int main(int argc, char** argv)
{
  if (argc == 1)
  {
    std::cout << "No inpu file specified." << std::endl;
    return 1;
  }
  // input file where the adjacency list representation of the graph is
  std::ifstream inFile(argv[1]);  
  if (!inFile.good())
  {
    std::cout << "Error in reading file: " << argv[1] << std::endl;
    return 2;
  }

  // read graph
  std::map< int, std::vector<int> > graph; // the original graph
  std::map< int, std::vector<int> > graphReverse; // the edge reversed graph
  std::set<int> idxNodes;
  int tail, head;
  while (inFile >> tail >> head)
  {
    graph[tail].push_back(head);
    graphReverse[head].push_back(tail);
    idxNodes.insert(tail);
    idxNodes.insert(head);
  }
  inFile.close();
  
  // Depth First Search (DFS) on graphReverse for calculating finishing time
  std::vector<int> sortedIdxNodes; // the idx of nodes sorted by its finishing time
  DFS_LoopFinishingTime(idxNodes, graphReverse, sortedIdxNodes);  

  
  // Depth First Search (DFS) on graph for assigning the strongly connected componenets
  std::map<int, int> leader;
  DFS_LoopAssignLeader(graph, sortedIdxNodes, leader);

  // SCC
  std::map<int, std::vector<int> > scc;  
  for(std::map<int,int>::iterator it = leader.begin(); it != leader.end(); it++)
  {
    scc[it->second].push_back(it->first);
  }  
  for(std::map<int,std::vector<int> >::iterator it = scc.begin(); it != scc.end(); it++)
  {
    std::cout << it->second.size() << std::endl;
  }  
  return 0;  
}
