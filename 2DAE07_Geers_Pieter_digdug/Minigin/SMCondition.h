#pragma once
class GameObject;
class SMCondition
{
public:
	SMCondition() = default;
	virtual ~SMCondition() = default;

	virtual bool IsTriggered(int) = 0;
};

