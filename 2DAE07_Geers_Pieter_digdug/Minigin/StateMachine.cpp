#include "MiniginPCH.h"
#include "StateMachine.h"
#include "SMState.h"
#include "SMTransition.h"

//=================================================================//
// Inspiration for this class from EliteEngine::FiniteStateMachine //
//=================================================================//


StateMachine::StateMachine(std::vector<SMState*> states, SMState* initState, int idx)
	:m_States(states)
	,m_CurrentState(initState)
	,m_AgentIndex(idx)
{
	m_CurrentState->RunEntryActions(idx);
}

StateMachine::~StateMachine()
{
	if (m_CurrentState != nullptr)
	{
		//delete m_CurrentState;
		m_CurrentState = nullptr;
	}
	for (auto t : m_States)
	{
		if (t != nullptr)
		{
			delete t;
			t = nullptr;
		}
	}
}

void StateMachine::Update()
{
	auto transitions = m_CurrentState->GetTransition();
	auto isTriggered = false;
	SMTransition* triggeredTransition{};

	for (auto tran : transitions)
	{
		if (tran->IsTriggered(m_AgentIndex))
		{
			isTriggered = true;
			triggeredTransition = tran;
			break;
		}
	}

	if (isTriggered)
	{
		const auto targetState = triggeredTransition->GetTargetState();

		m_CurrentState->RunExitActions(m_AgentIndex);
		targetState->RunEntryActions(m_AgentIndex);
		m_CurrentState = targetState;
	}
	else
		m_CurrentState->RunAction(m_AgentIndex);
}