#pragma once
#include "Command.h"
#include "DigDugCharacterComp.h"
#include "DigDugWeaponComp.h"

class MoveRightCommand final : public Command
{
public:
	void Execute() override
	{
		auto& P1 = ServiceLocator::GetPlayer(static_cast<int>(PlayerOne));
		P1->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::right);
	}
};

class MoveLeftCommand final : public Command
{
public:
	void Execute() override
	{
		auto& P1 = ServiceLocator::GetPlayer(static_cast<int>(PlayerOne));
		P1->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::left);
	}
};

class MoveUpCommand final : public Command
{
public:
	void Execute() override
	{
		auto& P1 = ServiceLocator::GetPlayer(static_cast<int>(PlayerOne));
		P1->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::up);
	}
};

class MoveDownCommand final : public Command
{
public:
	void Execute() override
	{
		auto& P1 = ServiceLocator::GetPlayer(static_cast<int>(PlayerOne));
		P1->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::down);
	}
};

class DigDugAttackCommand final : public Command
{
	void Execute() override
	{
		auto& P1 = ServiceLocator::GetPlayer(static_cast<int>(PlayerOne));
		auto gameObject = P1->GetChild("Weapon");
		auto charComp = P1->GetComponent<DigDugCharacterComp>();
		if (!charComp->GetIsPlayerDigging())
		{
			gameObject->GetComponent<DigDugWeaponComp>()->AttackDigDug(charComp->GetCurrentDirection());
			charComp->FreezeForTime(0.2f);
		}
	}
};