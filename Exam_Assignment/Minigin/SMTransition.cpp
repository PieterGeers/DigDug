#include "MiniginPCH.h"
#include "SMTransition.h"
#include "Debug.h"
#include "SMCondition.h"
#include "SMState.h"

SMTransition::SMTransition(std::vector<SMCondition*> conditions, SMState* targetState)
	:m_TargetState(targetState)
	,m_Conditions(conditions)
{
}

SMTransition::~SMTransition()
{
	if (m_TargetState != nullptr)
	{
		m_TargetState = nullptr;
	}
	for (auto c : m_Conditions)
	{
		if (c != nullptr)
		{
			delete c;
			c = nullptr;
		}
	}
}

bool SMTransition::IsTriggered(int idx) const
{
	for (auto condition : m_Conditions)
	{
		if (condition->IsTriggered(idx))
			return true;
	}
	return false;
}

void SMTransition::SetTargetState(SMState* targetState)
{
	m_TargetState = targetState;
}

void SMTransition::SetConditions(std::vector<SMCondition*> conditions)
{
	for (auto condition : conditions)
	{
		const auto it = std::find(m_Conditions.begin(), m_Conditions.end(), condition);
		if (it == m_Conditions.end())
			m_Conditions.push_back(condition);
		else
			Debug::LogWarning("cannot add the same condition twice");
	}
}

void SMTransition::SetCondition(SMCondition* condition)
{
	const auto it = std::find(m_Conditions.begin(), m_Conditions.end(), condition);
	if (it == m_Conditions.end())
		m_Conditions.push_back(condition);
	else
		Debug::LogWarning("cannot add the same condition twice");

}