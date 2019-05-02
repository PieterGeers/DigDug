#pragma once
#include "Command.h"
#include "DigDugCharacterComp.h"

class MoveRightCommand final : public Command
{
public:
	void Execute() override
	{
		auto& P1 = ServiceLocator::GetP1();
		P1->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::right);
	}
};

class MoveLeftCommand final : public Command
{
public:
	void Execute() override
	{
		auto& P1 = ServiceLocator::GetP1();
		P1->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::left);
	}
};

class MoveUpCommand final : public Command
{
public:
	void Execute() override
	{
		auto& P1 = ServiceLocator::GetP1();
		P1->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::up);
	}
};

class MoveDownCommand final : public Command
{
public:
	void Execute() override
	{
		auto& P1 = ServiceLocator::GetP1();
		P1->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::down);
	}
};

class DigDugAttackCommand final : public Command
{
	void Execute() override
	{
		/*const auto component = character->GetComponent<WeaponComponent>();
		const auto charComp = character->GetComponent<CharacterComponent>();
		if (component == nullptr)
			return;
		if (charComp == nullptr)
			return;
		switch (charComp->GetCurrentDirection())
		{
		case up:
			component->SetActive(0, 0, 0, 0);
			break;
		case down:
			component->SetActive(0, 1, 0, 0);
			break;
		case left:
			component->SetActive(0, 3, 0, 0);
			break;
		case right:
			component->SetActive(0, 2, 0, 0);
			break;
		case none: break;
		default:;
		}*/
	}
};