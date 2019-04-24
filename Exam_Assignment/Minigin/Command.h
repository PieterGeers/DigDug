#pragma once
#include "GameObject.h"
#include "CharacterComponent.h"
#include "ButtonComponent.h"
#include "WeaponComponent.h"

class Command
{
public:
	virtual void Execute(const std::shared_ptr<dae::GameObject>&) = 0;
	virtual ~Command() = default;
};

class NullCommand final : public Command
{
public:
	void Execute(const std::shared_ptr<dae::GameObject>&) override {}
};

class MoveRightCommand final : public Command
{
public:
	void Execute(const std::shared_ptr<dae::GameObject>& object) override
	{
		auto component = object->GetComponent<CharacterComponent>();
		if (component->GetCurrentDirection() != Direction::right)
		{
			component->SetPreviousDirection(component->GetCurrentDirection());
			component->SetCurrentDirection(Direction::right);
			component->SetIsMovingAutomatic(true);
		}
		if (int(object->GetTransform()->GetPosition().y) % component->GetGridSize() != 0)
		{
			if (component->GetPreviousDirection() == Direction::up)
				component->MoveUp(-2);
			else
				component->MoveUp(2);
		}
		else
		{
			object->GetComponent<CharacterComponent>()->MoveRight(2);
			component->SetIsMovingAutomatic(false);
		}
	}
};

class MoveLeftCommand final : public Command
{
public:
	void Execute(const std::shared_ptr<dae::GameObject>& object) override
	{
		auto component = object->GetComponent<CharacterComponent>();
		if (component->GetCurrentDirection() != Direction::left)
		{
			component->SetPreviousDirection(component->GetCurrentDirection());
			component->SetCurrentDirection(Direction::left);
			component->SetIsMovingAutomatic(true);
		}
		if (int(object->GetTransform()->GetPosition().y) % component->GetGridSize() != 0)
		{
			if (component->GetPreviousDirection() == Direction::up)
				component->MoveUp(-2); 
			else
				component->MoveUp(2);
		}
		else
		{
			component->MoveRight(-2);
			component->SetIsMovingAutomatic(false);
		}
	}
};

class MoveUpCommand final : public Command
{
public:
	void Execute(const std::shared_ptr<dae::GameObject>& object) override
	{
		auto component = object->GetComponent<CharacterComponent>();
		if (component->GetCurrentDirection() != Direction::up)
		{
			component->SetPreviousDirection(component->GetCurrentDirection());
			component->SetCurrentDirection(Direction::up);
			component->SetIsMovingAutomatic(true);
		}
		if (int(object->GetTransform()->GetPosition().x) % component->GetGridSize() != 0)
		{
			if (component->GetPreviousDirection() == Direction::left)
				component->MoveRight(-2);
			else
				component->MoveRight(2);
		}
		else
		{
			object->GetComponent<CharacterComponent>()->MoveUp(-2);
			component->SetIsMovingAutomatic(false);
		}
	}
};

class MoveDownCommand final : public Command
{
public:
	void Execute(const std::shared_ptr<dae::GameObject>& object) override
	{
		auto component = object->GetComponent<CharacterComponent>();
		if (component->GetCurrentDirection() != Direction::down)
		{
			component->SetPreviousDirection(component->GetCurrentDirection());
			component->SetCurrentDirection(Direction::down);
			component->SetIsMovingAutomatic(true);
		}
		if (int(object->GetTransform()->GetPosition().x) % component->GetGridSize() != 0)
		{
			if (component->GetPreviousDirection() == Direction::left)
				component->MoveRight(-2);
			else
				component->MoveRight(2);
		}
		else
		{
			object->GetComponent<CharacterComponent>()->MoveUp(2);
			component->SetIsMovingAutomatic(false);
		}
	}
};

class ButtonSelectCommand final : public Command
{
public:
	void Execute(const std::shared_ptr<dae::GameObject>& button) override
	{
		const auto component = button->GetComponent<ButtonComponent>();
		if (component == nullptr)
			return;
		component->ExecuteButton();
	}
};

class DigDugAttackCommand final : public Command
{
public:
	void Execute(const std::shared_ptr<dae::GameObject>& character) override
	{
		const auto component = character->GetComponent<WeaponComponent>();
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
		default: ;
		}
	}
};