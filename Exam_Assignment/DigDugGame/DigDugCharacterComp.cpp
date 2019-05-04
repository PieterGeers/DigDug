#include "pch.h"
#include "DigDugCharacterComp.h"
#include "Animator.h"
#include "TransformComponent.h"
#include "GameTime.h"

DigDugCharacterComp::DigDugCharacterComp(Boundaries levelBounds)
	:CharacterComponent(std::move(levelBounds))
{
}

void DigDugCharacterComp::Update()
{
	if (m_Freeze)
	{
		m_FreezeTime -= dae::GameTime::GetInstance().DeltaT();
		if (m_FreezeTime <= 0.0f)
			m_Freeze = false;
	}
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
	if (m_CanMove && !m_Freeze)
	{
		if (amount < 0 && GetTransform()->GetPosition().x > m_Boundaries.left ||
			amount > 0 && GetTransform()->GetPosition().x < m_Boundaries.right)
		{
			if (amount < 0 && !m_IsDigging /*left*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("Left");
			else if (amount < 0 && m_IsDigging /*left dig*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("LeftDig");
			else if (amount > 0 && !m_IsDigging /*right*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("Right");
			else if (amount > 0 && m_IsDigging /*right dig*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("RightDig");
			GetGameObject()->Translate(amount, 0, 0);
			m_CanMove = false;
		}
	}
}

void DigDugCharacterComp::MoveUp(float amount)
{
	if (m_CanMove && !m_Freeze)
	{
		if (amount < 0 && GetTransform()->GetPosition().y > m_Boundaries.top ||
			amount > 0 && GetTransform()->GetPosition().y < m_Boundaries.bottom)
		{
			if (amount < 0 && !m_IsDigging/*up*/)
				GetPreviousDirection() == Direction::right ? GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("RightUp") : GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("LeftUp");
			else if (amount < 0 && m_IsDigging /*up dig*/)
				GetPreviousDirection() == Direction::right ? GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("RightUpDig") : GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("LeftUpDig");
			else if (amount > 0 && !m_IsDigging /*down*/)
				GetPreviousDirection() == Direction::right ? GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("RightDown") : GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("LeftDown");
			else if (amount > 0 && m_IsDigging /*down dig*/)
				GetPreviousDirection() == Direction::right ? GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("RightDownDig") : GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("LeftDownDig");

			GetGameObject()->Translate(0, amount, 0);
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
		if (int(GetTransform()->GetPosition().y) % m_GridSize != 0)
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
		if (int(GetTransform()->GetPosition().x) % m_GridSize != 0)
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

void DigDugCharacterComp::FreezeForTime(float time)
{
	m_Freeze = true;
	m_FreezeTime = time;
}
