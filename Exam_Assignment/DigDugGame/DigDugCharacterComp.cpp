#include "pch.h"
#include "DigDugCharacterComp.h"
#include "TextureRenderComponent.h"


DigDugCharacterComp::DigDugCharacterComp(std::shared_ptr<dae::GameObject>& character, Boundaries levelBounds)
	:CharacterComponent(character, std::move(levelBounds))
{
}

void DigDugCharacterComp::Update()
{
}

void DigDugCharacterComp::FixedUpdate()
{
	if (!m_CanMove)
		m_CanMove = true;
}

void DigDugCharacterComp::Render()
{
}

void DigDugCharacterComp::SetTransform(float, float, float)
{
}

void DigDugCharacterComp::MoveRight(float amount)
{
	if (m_CanMove)
	{
		if (amount < 0 && m_pCharacter->GetTransform()->GetPosition().x > m_Boundaries.left ||
			amount > 0 && m_pCharacter->GetTransform()->GetPosition().x < m_Boundaries.right)
		{
			if (amount < 0 && !m_IsDigging /*left*/)
				SetActiveAnimation("Left");
			else if (amount < 0 && m_IsDigging /*left dig*/)
				SetActiveAnimation("LeftDig");
			else if (amount > 0 && !m_IsDigging /*right*/)
				SetActiveAnimation("Right");
			else if (amount > 0 && m_IsDigging /*right dig*/)
				SetActiveAnimation("RightDig");
			m_pCharacter->Translate(amount, 0, 0);
			m_CanMove = false;
		}
	}
}

void DigDugCharacterComp::MoveUp(float amount)
{
	if (m_CanMove)
	{
		if (amount < 0 && m_pCharacter->GetTransform()->GetPosition().y > m_Boundaries.top ||
			amount > 0 && m_pCharacter->GetTransform()->GetPosition().y < m_Boundaries.bottom)
		{
			if (amount < 0 && !m_IsDigging/*up*/)
				GetPreviousDirection() == Direction::right ? SetActiveAnimation("RightUp") : SetActiveAnimation("LeftUp");
			else if (amount < 0 && m_IsDigging /*up dig*/)
				GetPreviousDirection() == Direction::right ? SetActiveAnimation("RightUpDig") : SetActiveAnimation("LeftUpDig");
			else if (amount > 0 && !m_IsDigging /*down*/)
				GetPreviousDirection() == Direction::right ? SetActiveAnimation("RightDown") : SetActiveAnimation("LeftDown");
			else if (amount > 0 && m_IsDigging /*down dig*/)
				GetPreviousDirection() == Direction::right ? SetActiveAnimation("RightDownDig") : SetActiveAnimation("LeftDownDig");

			m_pCharacter->Translate(0, amount, 0);
			m_CanMove = false;
		}
	}
}

void DigDugCharacterComp::ExecuteMovement(Direction dir)
{
	if (current != dir)
	{
		previous = current;
		current = dir;
		m_IsMoveAutomatic = true;
	}
	if (dir == Direction::left || dir == Direction::right)
	{
		if (int(m_pCharacter->GetTransform()->GetPosition().y) % m_GridSize != 0)
		{
			if (previous == Direction::up)
				MoveUp(-2);
			else
				MoveUp(2);
		}
		else
		{
			(dir == Direction::left) ? 	MoveRight(-2) : MoveRight(2);
			m_IsMoveAutomatic = false;
		}
	}
	else if (dir == Direction::up || dir == Direction::down)
	{
		if (int(m_pCharacter->GetTransform()->GetPosition().x) % m_GridSize != 0)
		{
			if (previous == Direction::left)
				MoveRight(-2);
			else
				MoveRight(2);
		}
		else
		{
			(dir == Direction::up) ? MoveUp(-2) : MoveUp(2);
			m_IsMoveAutomatic = false;
		}
	}
}
