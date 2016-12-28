#ifndef _DFS_H
#define _DFS_H 1

#include <vector>
#include <map>
#include <set>

void DFS_LoopFinishingTime(std::set<int> idxNodes,
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
#endif

