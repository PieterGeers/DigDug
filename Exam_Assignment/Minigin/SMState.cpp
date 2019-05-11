#include "MiniginPCH.h"
#include "SMState.h"
#include "SMAction.h"
#include "SMTransition.h"
#include "Debug.h"

SMState::SMState(std::vector<SMAction*> entryActions, std::vector<SMAction*> actions,
	std::vector<SMAction*> exitActions, std::vector<SMTransition*> transitions)
	:m_EntryActions(entryActions)
	,m_Actions(actions)
	,m_ExitActions(exitActions)
	,m_Transitions(transitions)
{
}

SMState::~SMState()
{
	for (auto a : m_EntryActions)
	{
		if (a != nullptr)
		{
			delete a;
			a = nullptr;
		}
	}
	for (auto a : m_ExitActions)
	{
		if (a != nullptr)
		{
			delete a;
			a = nullptr;
		}
	}
	for (auto a : m_Actions)
	{
		if (a != nullptr)
		{
			delete a;
			a = nullptr;
		}
	}
	for (auto a : m_Transitions)
	{
		if (a != nullptr)
		{
			delete a;
			a = nullptr;
		}
	}
}

void SMState::SetEntryActions(std::vector<SMAction*> entryActions)
{
	for (auto action : entryActions)
	{
		const auto it = std::find(m_EntryActions.begin(), m_EntryActions.end(), action);
		if (it == m_EntryActions.end())
			m_EntryActions.push_back(action);
		else
			Debug::LogWarning("Trying to add the same EntryActions twice");
	}
}

void SMState::SetEntryAction(SMAction* entryAction)
{
	const auto it = std::find(m_EntryActions.begin(), m_EntryActions.end(), entryAction);
	if (it == m_EntryActions.end())
		m_EntryActions.push_back(entryAction);
	else
		Debug::LogWarning("Trying to add the same EntryActions twice");
}

void SMState::SetActions(std::vector<SMAction*> actions)
{
	for (auto action : actions)
	{
		const auto it = std::find(m_Actions.begin(), m_Actions.end(), action);
		if (it == m_Actions.end())
			m_Actions.push_back(action);
		else
			Debug::LogWarning("Trying to add the same Actions twice");
	}
}

void SMState::SetAction(SMAction* action)
{
	const auto it = std::find(m_Actions.begin(), m_Actions.end(), action);
	if (it == m_Actions.end())
		m_Actions.push_back(action);
	else
		Debug::LogWarning("Trying to add the same Actions twice");
}

void SMState::SetExitActions(std::vector<SMAction*> exitActions)
{
	for (auto action : exitActions)
	{
		const auto it = std::find(m_ExitActions.begin(), m_ExitActions.end(), action);
		if (it == m_ExitActions.end())
			m_ExitActions.push_back(action);
		else
			Debug::LogWarning("Trying to add the same ExitActions twice");
	}
}

void SMState::SetExitAction(SMAction* exitAction)
{
	const auto it = std::find(m_ExitActions.begin(), m_ExitActions.end(), exitAction);
	if (it == m_ExitActions.end())
		m_ExitActions.push_back(exitAction);
	else
		Debug::LogWarning("Trying to add the same ExitActions twice");

}

void SMState::SetTransitions(std::vector<SMTransition*> transitions)
{
	for (auto action : transitions)
	{
		const auto it = std::find(m_Transitions.begin(), m_Transitions.end(), action);
		if (it == m_Transitions.end())
			m_Transitions.push_back(action);
		else
			Debug::LogWarning("Trying to add the same Transition twice");
	}
}

void SMState::SetTransition(SMTransition* transition)
{
	const auto it = std::find(m_Transitions.begin(), m_Transitions.end(), transition);
	if (it == m_Transitions.end())
		m_Transitions.push_back(transition);
	else
		Debug::LogWarning("Trying to add the same Transition twice");
}

void SMState::RunAction(int idx) const
{
	for (auto action : m_Actions)
		action->Invoke(idx);
}

void SMState::RunEntryActions(int idx) const
{
	for (auto action : m_EntryActions)
		action->Invoke(idx);
}

void SMState::RunExitActions(int idx) const
{
	for (auto action : m_ExitActions)
		action->Invoke(idx);
}