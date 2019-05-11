#pragma once
#include <vector>
class GameObject;
class SMAction;
class SMTransition;
class SMState final
{
public:
	SMState(std::vector<SMAction*> entryActions, std::vector<SMAction*> actions,
		std::vector<SMAction*> exitActions, std::vector<SMTransition*> transitions);
	SMState() = default;
	~SMState();

	void SetEntryActions(std::vector<SMAction*> entryActions);
	void SetEntryAction(SMAction* entryAction);

	void SetActions(std::vector<SMAction*> actions);
	void SetAction(SMAction* action);

	void SetExitActions(std::vector<SMAction*> exitActions);
	void SetExitAction(SMAction* exitAction);

	void SetTransitions(std::vector<SMTransition*> transitions);
	void SetTransition(SMTransition* transition);

	void RunAction(int idx) const;
	void RunEntryActions(int idx) const;
	void RunExitActions(int idx) const;

	std::vector<SMTransition*> GetTransition() const { return m_Transitions; }

private:
	std::vector<SMAction*> m_EntryActions = {};
	std::vector<SMAction*> m_Actions = {};
	std::vector<SMAction*> m_ExitActions = {};
	std::vector<SMTransition*> m_Transitions = {};
};

