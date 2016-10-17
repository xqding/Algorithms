#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


void DFS_Loop(std::map< int, std::vector<int> > &graph,
	      std::vector<int> &sortedIdxNodes);
void DFS_Recursion(int s, std::map< int, std::vector<int> > &graph,
		   std::map<int,bool> &isExplored, std::vector<int> &sortedIdxNodes);

int main(int argc, char** argv)
{
  // input file where the adjacency list representation of the graph is
  std::ifstream inFile(argv[1]);
  if (!inFile.good())
  {
    std::cout << "Error in reading file: " << argv[1] << std::endl;
  }

  // read graph
  std::map< int, std::vector<int> > graph; // the original graph
  std::map< int, std::vector<int> > graphReverse; // the edge reversed graph
  int tail, head;
  int numNodes = 0;
  while (inFile >> tail >> head)
  {
    graph[tail].push_back(head);
    graph[head].push_back(tail);
    if (tail > numNodes) numNodes = tail;
    if (head > numNodes) numNodes = head;
  }
  inFile.close();
    
  // Depth First Search (DFS) on graphReverse for calculating finishing time
  std::vector<int> sortedIdxNodes; // the idx of nodes sorted by its finishing time
  DFS_Loop(graphReverse, sortedIdxNodes);
  for(std::vector<int>::iterator it = sortedIdxNodes.begin(); it != sortedIdxNodes.end(); it++)
  {
    std::cout << *it << std::endl;
  }
  return 0;  
}


// DFS functions
void DFS_Loop(std::map< int, std::vector<int> > &graph,
	      std::vector<int> &sortedIdxNodes)
{
  // mark all nodes as unexlored
  std::map<int,bool> isExplored;
  for(std::map< int, std::vector<int> >::iterator it = graph.begin(); it != graph.end(); it++)
  {
    isExplored[it->first] = false;
  }

  // DFS
  for(std::map< int, std::vector<int> >::iterator it = graph.begin(); it != graph.end(); it++)
  {
    if ( !isExplored[it->first] )
    {
      DFS_Recursion(it->first, graph, isExplored, sortedIdxNodes);
    }
  }  
};

void DFS_Recursion(int s, std::map< int, std::vector<int> > &graph,
		   std::map<int,bool> &isExplored, std::vector<int> &sortedIdxNodes)
{
  isExplored[s] = true;
  for(std::vector<int>::iterator i = graph[s].begin(); i != graph[s].end(); i++)
  {
    DFS_Recursion(*i, graph, isExplored, sortedIdxNodes);
  }
  sortedIdxNodes.push_back(s);
};
