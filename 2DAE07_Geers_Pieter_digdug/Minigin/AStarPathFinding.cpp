#include "MiniginPCH.h"
#include "AStarPathFinding.h"
#include "Connection.h"
#include "Node.h"
#include "algorithm"

//================================================================//
// Inspiration for this class from EliteEngine::EAStarPathFinding //
//================================================================//


std::vector<std::shared_ptr<Node>> AStarPathFinding::m_Graph;

std::vector<MVector2_INT> AStarPathFinding::FindPath(Node* pStartNode, Node* pEndNode,
	Heuristic heuristicFunction)
{
	std::vector<MVector2_INT> vPath;

	std::vector<Connection*> openList;
	std::vector<Connection*> closedList;

	Connection* pCurrentConnection{};

	for (auto c : pStartNode->GetConnection())
	{
		CalculateCost(c, pStartNode, pEndNode, heuristicFunction);
		openList.push_back(c);
	}

	while (!openList.empty())
	{
		auto LowestFScore = openList[0];
		for (auto c : openList)
		{
			if (c->GetFCost() < LowestFScore->GetFCost())
				LowestFScore = c;
		}
		pCurrentConnection = LowestFScore;

		openList.erase(std::remove(openList.begin(), openList.end(), pCurrentConnection), openList.end());
		closedList.push_back(pCurrentConnection);

		std::vector<Connection*> vpConnections = {};
		for (auto c : pCurrentConnection->GetEndNode()->GetConnection())
		{
			vpConnections.push_back(c);
		}

		const auto containsEndNode = [pEndNode](const Connection* a) {return a->GetEndNode() == pEndNode; };
		auto result = std::find_if(vpConnections.begin(), vpConnections.end(), containsEndNode);

		if (result != vpConnections.end())
		{
			(*result)->SetHeadConnection(pCurrentConnection);
			pCurrentConnection = (*result);
			break;
		}

		for (auto pC : vpConnections)
		{
			const auto containsPc = [pC](const Connection* a)
			{
				return (a->GetStartNode()->GetPosition() == pC->GetStartNode()->GetPosition() &&
					a->GetEndNode()->GetPosition() == pC->GetEndNode()->GetPosition()) || (a->GetStartNode()->GetPosition() == pC->GetEndNode()->GetPosition() &&
						a->GetEndNode()->GetPosition() == pC->GetStartNode()->GetPosition());
			};
			auto found = std::find_if(closedList.begin(), closedList.end(), containsPc);
			if (found != closedList.end())
				continue;

			auto found2 = std::find_if(openList.begin(), openList.end(), containsPc);
			if (found2 != openList.end())
				continue;

			pC->SetHeadConnection(pCurrentConnection);
			CalculateCost(pC, pStartNode, pEndNode, heuristicFunction);
			openList.push_back(pC);
		}
	}
	while (pCurrentConnection->GetStartNode()->GetPosition() != pStartNode->GetPosition())
	{
		vPath.push_back(pCurrentConnection->GetEndNode()->GetPosition());
		pCurrentConnection = pCurrentConnection->GetHeadConnection();
	}

	vPath.push_back(pCurrentConnection->GetEndNode()->GetPosition());
	vPath.push_back(pStartNode->GetPosition());

	std::reverse(vPath.begin(), vPath.end());
	return vPath;
}

void AStarPathFinding::CalculateCost(Connection* pc, Node* pStartNode,
	Node* pEndNode, Heuristic heuristicFunction)
{
	float currentGCost = 0;
	if (pc->GetHeadConnection() != nullptr)
		currentGCost = pc->GetHeadConnection()->GetGCost();

	MVector2_INT parentPos = pStartNode->GetPosition();
	if (pc->GetHeadConnection() != nullptr)
		parentPos = pc->GetHeadConnection()->GetStartNode()->GetPosition();

	MVector2_INT tempV = (pc->GetEndNode()->GetPosition() - parentPos).GetAbs();
	float gCost = heuristicFunction(static_cast<float>(tempV.x), static_cast<float>(tempV.y));
	pc->SetGCost(currentGCost + gCost);

	tempV = (pc->GetEndNode()->GetPosition() - pEndNode->GetPosition()).GetAbs();
	const float hCost = heuristicFunction(static_cast<float>(tempV.x), static_cast<float>(tempV.y));
	pc->SetHCost(hCost);
}
