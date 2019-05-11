#pragma once
class GameObject;
class SMState;
class SMCondition;
class SMTransition final
{
public:
	SMTransition(std::vector<SMCondition*> conditions, SMState* targetState);
	SMTransition() = default;
	~SMTransition();

	bool IsTriggered(int idx) const;

	void SetTargetState(SMState* targetState);

	void SetConditions(std::vector<SMCondition*> conditions);
	void SetCondition(SMCondition* condition);

	SMState* GetTargetState() const { return m_TargetState; }
private:
	SMState* m_TargetState;
	std::vector<SMCondition*> m_Conditions = {};
};

