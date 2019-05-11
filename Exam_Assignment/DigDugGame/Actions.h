#pragma once
#include "AgentComponent.h"
#include "SMAction.h"
#include "AStarPathFinding.h"
#include "TransformComponent.h"
#include "Heuristic.h"
class WalkAction final : public SMAction
{
public:
	void Invoke(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return;

		pAgent->SmoothWalkTo(pAgent->m_NextPosition);
	}
};

class FindNextPathAction final : public SMAction
{
public:
	void Invoke(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return;

		const int sIdx = pAgent->CalculateGridIndex();
		const int toIdx = pAgent->CalculateClosestPlayerIndex();
		pAgent->m_NextPosition = MVector2_INT{ static_cast<int>(pAgent->GetTransform()->GetPosition().x), static_cast<int>(pAgent->GetTransform()->GetPosition().y) };
		pAgent->m_CurrentPath = AStarPathFinding::FindPath(AStarPathFinding::GetGraph()[sIdx].get(), AStarPathFinding::GetGraph()[toIdx].get(), HeuristicFunction::Euclidean);
	}
};

class ChangeAnimation final : public SMAction
{
public:
	ChangeAnimation(const std::string& name) : m_Name(name) {}
	void Invoke(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return;
		pAgent->SetAnimation(m_Name);
	}
private:
	std::string m_Name;
};