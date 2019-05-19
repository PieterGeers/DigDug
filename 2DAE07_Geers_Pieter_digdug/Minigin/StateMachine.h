#pragma once
class SMState;
class GameObject;
class StateMachine final
{
public:
	StateMachine(std::vector<SMState*> states, SMState* initState, int idx);
	StateMachine() = default;
	~StateMachine();

	void Update();

private:
	std::vector<SMState*> m_States = {};
	SMState* m_CurrentState = nullptr;
	int m_AgentIndex;
};

