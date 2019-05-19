#pragma once
class GameObject;
class SMAction
{
public:
	SMAction() = default;
	virtual ~SMAction() = default;

	virtual void Invoke(int) = 0;
};

