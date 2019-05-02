#pragma once
#include "Structs.h"
typedef float(*Heuristic)(float, float);
class Node;
class Connection;
class AStarPathFinding
{
public:
	AStarPathFinding() {};
	~AStarPathFinding() = default;

	std::vector<MVector2_INT> FindPath(std::shared_ptr<Node> pStartNode, std::shared_ptr<Node> pEndNode, Heuristic heuristicFunction);

private:
	void CalculateCost(std::shared_ptr<Connection> pc, std::shared_ptr<Node> pStartNode, std::shared_ptr<Node> pEndNode, Heuristic heuristicFunction);
};

