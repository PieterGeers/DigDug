#pragma once
#include "Structs.h"
typedef float(*Heuristic)(float, float);
class Node;
class Connection;
class AStarPathFinding
{
public:
	AStarPathFinding() = default;
	~AStarPathFinding() = default;

	static std::vector<MVector2_INT> FindPath(Node* pStartNode, Node* pEndNode, Heuristic heuristicFunction);
	static std::vector<std::shared_ptr<Node>>& GetGraph() { return m_Graph; }
private:
	static void CalculateCost(Connection* pc, Node* pStartNode, Node* pEndNode, Heuristic heuristicFunction);
	static std::vector<std::shared_ptr<Node>> m_Graph;
};

