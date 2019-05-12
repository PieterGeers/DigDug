#pragma once
#include "AgentComponent.h"
#include "SMCondition.h"

class HasReachedNextPosition final : public SMCondition
{
public:
	bool IsTriggered(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return false;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return false;

		if (pAgent->m_HasReachedEndPosition)
		{
			pAgent->m_HasReachedEndPosition = false;
			return true;
		}
		return false;
	}
};

class StartGoingInvisible final : public SMCondition
{
public:
	bool IsTriggered(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return false;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return false;

		if (pAgent->m_IsInvisible && !pAgent->m_WasInvisible)
		{
			pAgent->m_WasInvisible = true;
			return true;
		}
		return false;
	}
};

class StopGoingInvisible final : public SMCondition
{
public:
	bool IsTriggered(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return false;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return false;

		if (!pAgent->m_IsInvisible && pAgent->m_WasInvisible)
		{
			pAgent->m_WasInvisible = false;
			return true;
		}
		return false;
	}
};

class AnimationChanged final : public SMCondition
{
public:
	bool IsTriggered(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return false;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return false;

		if (pAgent->m_HasAnimationChanged)
		{
			pAgent->m_HasAnimationChanged = false;
			return true;
		}
		return false;
	}
};

class StartBeingInflated final : public SMCondition
{
public:
	bool IsTriggered(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return false;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return false;

		if (pAgent->m_IsBeingInflated && pAgent->m_WasBeingInflated == false)
		{
			pAgent->m_WasBeingInflated = true;
			return true;
		}
		return false;
	}
};

class StopBeingInflated final : public SMCondition
{
public:
	bool IsTriggered(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return false;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return false;

		if (!pAgent->m_IsBeingInflated && pAgent->m_WasBeingInflated && !pAgent->m_IsDead)
		{
			pAgent->m_WasBeingInflated = false;
			return true;
		}
		return false;
	}
};

class IsDead final : public SMCondition
{
	bool IsTriggered(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return false;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return false;

		if (pAgent->m_IsDead)
		{
			return true;
		}
		return false;
	}
};

class IsHitByRock final : public SMCondition
{
	bool IsTriggered(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return false;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return false;

		if (pAgent->m_IsHitByFallingRock)
		{
			return true;
		}
		return false;
	}
};

class StopBeingIdle final : public SMCondition
{
	bool IsTriggered(int idx) override
	{
		auto& pAgentObject = ServiceLocator::GetAgent(idx);
		if (pAgentObject == nullptr)
			return false;
		auto pAgent = pAgentObject->GetComponent<AgentComponent>();
		if (pAgent == nullptr)
			return false;

		if (!pAgent->m_IsIdle)
		{
			return true;
		}
		return false;
	}
};