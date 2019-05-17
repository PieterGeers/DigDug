#pragma once
#include "ServiceLocator.h"
#include "InputManager.h"

class Command
{
public:
	virtual void Execute(int) = 0;
	virtual ~Command() = default;
};

class NullCommand final : public Command
{
public:
	void Execute(int) override {}
};

class ButtonSelectCommand final : public Command
{
public:
	void Execute(int) override
	{
		ServiceLocator::GetButtonManager()->GetActiveButtonComp()->ExecuteButton();
	}
};

class ButtonUpCommand final : public Command
{
public:
	void Execute(int) override
	{
		ServiceLocator::GetButtonManager()->ButtonUp();
	}
};

class ButtonDownCommand final : public Command
{
public:
	void Execute(int) override
	{
		ServiceLocator::GetButtonManager()->ButtonDown();
	}
};

class QuitCommand final : public Command
{
public:
	void Execute(int) override
	{
		InputManager::GetInstance().Quit();
	}
};