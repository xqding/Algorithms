#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

void DFS_LoopFinishingTime(int numNodes,
			   std::map< int, std::vector<int> > &graph,
			   std::vector<int> &sortedIdxNodes);
void DFS_RecursionFinishingTime(int s, std::map< int, std::vector<int> > &graph,
				std::map<int,bool> &isExplored,
				std::vector<int> &sortedIdxNodes);
void DFS_LoopAssignLeader(std::map< int, std::vector<int> > &graph,
			  std::vector<int> &sortedIdxNodes,
			  std::map<int, int> &leader);
void DFS_RecursionAssignLeader(int currentNodeIdx, int leaderIdx,
			       std::map< int, std::vector<int> > &graph,
			       std::map<int,bool> &isExplored,
			       std::map<int, int> &leader);

int main(int argc, char** argv)
{
  // input file where the adjacency list representation of the graph is
  std::ifstream inFile(argv[1]);
  // std::ifstream inFile("./test/testSCC.txt");
  if (!inFile.good())
  {
    std::cout << "Error in reading file: " << argv[1] << std::endl;
    return 1;
  }

  // read graph
  std::map< int, std::vector<int> > graph; // the original graph
  std::map< int, std::vector<int> > graphReverse; // the edge reversed graph
  int tail, head;
  int numNodes = 0;
  while (inFile >> tail >> head)
  {
    graph[tail].push_back(head);
    graphReverse[head].push_back(tail);
    if (tail > numNodes) numNodes = tail;
    if (head > numNodes) numNodes = head;
  }
  inFile.close();
  
  // Depth First Search (DFS) on graphReverse for calculating finishing time
  std::vector<int> sortedIdxNodes; // the idx of nodes sorted by its finishing time
  DFS_LoopFinishingTime(numNodes, graphReverse, sortedIdxNodes);  

  // Depth First Search (DFS) on graph for assigning the strongly connected componenets
  std::map<int, int> leader;
  DFS_LoopAssignLeader(graph, sortedIdxNodes, leader);

  // for(std::map<int,int>::iterator it = leader.begin(); it != leader.end(); it++)
  // {
  //   std::cout << it->first << ":" << it->second << std::endl;
  // }

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

void DFS_LoopAssignLeader(std::map< int, std::vector<int> > &graph,
			  std::vector<int> &sortedIdxNodes,
			  std::map<int, int> &leader)
{
  // mark all nodes as unexlored
  std::map<int,bool> isExplored;
  for(int i = 1; i <= sortedIdxNodes.size(); i++)
  {
    isExplored[i] = false;
  }

  // assign leader idx for each node
  int leaderIdx;
  for(std::vector<int>::reverse_iterator it = sortedIdxNodes.rbegin();
      it != sortedIdxNodes.rend(); it++)
  {
    if (!isExplored[*it])
    {
      leaderIdx = *it;
      DFS_RecursionAssignLeader(*it, leaderIdx, graph, isExplored, leader);
    }
  }
};

void DFS_RecursionAssignLeader(int currentNodeIdx, int leaderIdx,
			       std::map< int, std::vector<int> > &graph,
			       std::map<int,bool> &isExplored,
			       std::map<int, int> &leader)
{
  if(!isExplored[currentNodeIdx])
  {
    isExplored[currentNodeIdx] = true;
    leader[currentNodeIdx] = leaderIdx;
    for(std::vector<int>::iterator it = graph[currentNodeIdx].begin(); it != graph[currentNodeIdx].end(); it++)
    {
      DFS_RecursionAssignLeader(*it, leaderIdx, graph, isExplored, leader);
    }    
  }
};



// DFS functions
void DFS_LoopFinishingTime(int numNodes, std::map< int, std::vector<int> > &graph,
	      std::vector<int> &sortedIdxNodes)
{
  // mark all nodes as unexlored
  std::map<int,bool> isExplored;
  for(int i = 1; i <= numNodes; i++)
  {
    isExplored[i] = false;
  }

  // DFS
  for(std::map< int, std::vector<int> >::iterator it = graph.begin(); it != graph.end(); it++)
  {
    if ( !isExplored[it->first] )
    {
      DFS_RecursionFinishingTime(it->first, graph, isExplored, sortedIdxNodes);
    }
  }  
};

void DFS_RecursionFinishingTime(int s, std::map< int, std::vector<int> > &graph,
		   std::map<int,bool> &isExplored, std::vector<int> &sortedIdxNodes)
{
  if (!isExplored[s])
  {
    isExplored[s] = true;
    for(std::vector<int>::iterator it = graph[s].begin(); it != graph[s].end(); it++)
    {
      DFS_RecursionFinishingTime(*it, graph, isExplored, sortedIdxNodes);
    }
    sortedIdxNodes.push_back(s);
  }
};
