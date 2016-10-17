#include <vector>
#include <map>

#include "DFS.h"
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
