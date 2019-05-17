#pragma once
#include "Command.h"
#include "DigDugCharacterComp.h"
#include "DigDugWeaponComp.h"
#include "FygarCharacterComp.h"

class MoveRightCommand final : public Command
{
public:
	void Execute(int idx) override
	{
		auto& P = ServiceLocator::GetPlayer(idx);
		if (P == nullptr)
			return;
		if (P->GetComponent<DigDugCharacterComp>()->GetIsDead())
			return;

		P->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::right);
	}
};

class FygarMoveRightCommand final : public Command
{
public:
	void Execute(int idx) override
	{
		auto& P = ServiceLocator::GetPlayer(idx);
		if (P == nullptr)
			return;
		if (P->GetComponent<FygarCharacterComp>()->GetIsDead())
			return;

		P->GetComponent<FygarCharacterComp>()->ExecuteMovement(Direction::right);
	}
};


class MoveLeftCommand final : public Command
{
public:
	void Execute(int idx) override
	{
		auto& P = ServiceLocator::GetPlayer(idx);
		if (P == nullptr)
			return;
		if (P->GetComponent<DigDugCharacterComp>()->GetIsDead())
			return;

		P->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::left);
	}
};

class FygarMoveLeftCommand final : public Command
{
public:
	void Execute(int idx) override
	{
		auto& P = ServiceLocator::GetPlayer(idx);
		if (P == nullptr)
			return;
		if (P->GetComponent<FygarCharacterComp>()->GetIsDead())
			return;

		P->GetComponent<FygarCharacterComp>()->ExecuteMovement(Direction::left);
	}
};

class MoveUpCommand final : public Command
{
public:
	void Execute(int idx) override
	{
		auto& P = ServiceLocator::GetPlayer(idx);
		if (P == nullptr)
			return;
		if (P->GetComponent<DigDugCharacterComp>()->GetIsDead())
			return;

		P->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::up);
	}
};

class FygarMoveUpCommand final : public Command
{
public:
	void Execute(int idx) override
	{
		auto& P = ServiceLocator::GetPlayer(idx);
		if (P == nullptr)
			return;
		if (P->GetComponent<FygarCharacterComp>()->GetIsDead())
			return;

		P->GetComponent<FygarCharacterComp>()->ExecuteMovement(Direction::up);
	}
};


class MoveDownCommand final : public Command
{
public:
	void Execute(int idx) override
	{
		auto& P = ServiceLocator::GetPlayer(idx);
		if (P == nullptr)
			return;
		if (P->GetComponent<DigDugCharacterComp>()->GetIsDead())
			return;

		P->GetComponent<DigDugCharacterComp>()->ExecuteMovement(Direction::down);
	}
};

class FygarMoveDownCommand final : public Command
{
public:
	void Execute(int idx) override
	{
		auto& P = ServiceLocator::GetPlayer(idx);
		if (P == nullptr)
			return;
		if (P->GetComponent<FygarCharacterComp>()->GetIsDead())
			return;

		P->GetComponent<FygarCharacterComp>()->ExecuteMovement(Direction::down);
	}
};

class DigDugAttackCommand final : public Command
{
	void Execute(int idx) override
	{
		auto& P = ServiceLocator::GetPlayer(idx);
		if (P == nullptr)
			return;
		if (P->GetComponent<DigDugCharacterComp>()->GetIsDead())
			return;
		auto gameObject = P->GetChild("Weapon");
		auto charComp = P->GetComponent<DigDugCharacterComp>();
		if (!charComp->GetIsPlayerDigging())
		{
			gameObject->GetComponent<DigDugWeaponComp>()->AttackDigDug(charComp->GetCurrentDirection());
			charComp->FreezeForTime(0.2f);
		}
	}
};

class FygarAttackCommand final : public Command
{
	void Execute(int idx) override
	{
		auto& P = ServiceLocator::GetPlayer(idx);
		if (P == nullptr)
			return;
		if (P->GetComponent<FygarCharacterComp>()->GetIsDead())
			return;

		auto gameObject = P->GetChild("EnemyWeapon");
		auto charComp = P->GetComponent<FygarCharacterComp>();
		if (!charComp->GetIsPlayerInvisible())
		{
			gameObject->GetComponent<DigDugWeaponComp>()->AttackFygar(charComp->GetCurrentDirection());
			charComp->FreezeForTime(0.6f);
		}
	}
};