#include "MiniginPCH.h"
#include "AStarPathFinding.h"
#include "Connection.h"
#include "Node.h"
#include "algorithm"

std::vector<MVector2_INT> AStarPathFinding::FindPath(std::shared_ptr<Node> pStartNode, std::shared_ptr<Node> pEndNode,
	Heuristic heuristicFunction)
{
	std::vector<MVector2_INT> vPath;

	std::vector<std::shared_ptr<Connection>> openList;
	std::vector<std::shared_ptr<Connection>> closedList;

	std::shared_ptr<Connection> pCurrentConnection{};

	for (const auto c : pStartNode->GetConnection())
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

		std::vector<std::shared_ptr<Connection>> vpConnections = {};
		for (auto c : pCurrentConnection->GetEndNode()->GetConnection())
		{
			vpConnections.push_back(c);
		}

		const auto containsEndNode = [pEndNode](const std::shared_ptr<Connection> a) {return a->GetEndNode() == pEndNode; };
		auto result = std::find_if(vpConnections.begin(), vpConnections.end(), containsEndNode);

		if (result != vpConnections.end())
		{
			(*result)->SetHeadConnection(pCurrentConnection);
			pCurrentConnection = (*result);
			break;
		}

		for (auto pC : vpConnections)
		{
			const auto containsPc = [pC](const std::shared_ptr<Connection> a) {return a == pC; };
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

	while (pCurrentConnection->GetStartNode() != pStartNode)
	{
		vPath.push_back(pCurrentConnection->GetEndNode()->GetPosition());
		pCurrentConnection = pCurrentConnection->GetHeadConnection();
	}

	vPath.push_back(pCurrentConnection->GetEndNode()->GetPosition());
	vPath.push_back(pStartNode->GetPosition());

	std::reverse(vPath.begin(), vPath.end());
	return vPath;
}

void AStarPathFinding::CalculateCost(std::shared_ptr<Connection> pc, std::shared_ptr<Node> pStartNode,
	std::shared_ptr<Node> pEndNode, Heuristic heuristicFunction)
{
	float currentGCost = 0;
	if (pc->GetHeadConnection() != nullptr)
		currentGCost = pc->GetHeadConnection()->GetGCost();

	MVector2_INT parentPos = pStartNode->GetPosition();
	if (pc->GetHeadConnection() != nullptr)
		parentPos = pc->GetHeadConnection()->GetStartNode()->GetPosition();

	MVector2_INT tempV = (pc->GetEndNode()->GetPosition() - parentPos).GetAbs();
	const float gCost = heuristicFunction(static_cast<float>(tempV.x), static_cast<float>(tempV.y));
	pc->SetGCost(currentGCost + gCost);

	tempV = (pc->GetEndNode()->GetPosition() - pEndNode->GetPosition()).GetAbs();
	const float hCost = heuristicFunction(static_cast<float>(tempV.x), static_cast<float>(tempV.y));
	pc->SetHCost(hCost);
}
