#include "pch.h"
#include "FygarCharacterComp.h"
#include "GameTime.h"
#include "Animator.h"


FygarCharacterComp::FygarCharacterComp(Boundaries levelBounds, int index)
	:CharacterComponent(std::move(levelBounds))
	, m_Index(index)
{
}

void FygarCharacterComp::Update()
{
	if (m_Freeze)
	{
		m_FreezeTime -= dae::GameTime::GetInstance().DeltaT();
		if (m_FreezeTime <= 0.0f)
			m_Freeze = false;
	}
}

void FygarCharacterComp::FixedUpdate()
{
	if (!m_CanMove)
		m_CanMove = true;
}

void FygarCharacterComp::Render()
{
}

void FygarCharacterComp::SetTransform(float, float, float)
{
}

void FygarCharacterComp::MoveRight(float amount)
{
	if (m_CanMove && !m_Freeze)
	{
		if (amount < 0 && GetTransform()->GetPosition().x > m_Boundaries.left ||
			amount > 0 && GetTransform()->GetPosition().x < m_Boundaries.right)
		{
			if (amount < 0 && !m_IsInvisible /*left*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("Walk");
			else if (amount < 0 && m_IsInvisible /*left invis*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("Invisible");
			else if (amount > 0 && !m_IsInvisible /*right*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("Walk");
			else if (amount > 0 && m_IsInvisible /*right invis*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("Invisible");
			GetGameObject()->Translate(amount, 0, 0);
			m_CanMove = false;
		}
	}
}

void FygarCharacterComp::MoveUp(float amount)
{
	if (m_CanMove && !m_Freeze)
	{
		if (amount < 0 && GetTransform()->GetPosition().y > m_Boundaries.top ||
			amount > 0 && GetTransform()->GetPosition().y < m_Boundaries.bottom)
		{
			if (amount < 0 && !m_IsInvisible/*up*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("Walk");
			else if (amount < 0 && m_IsInvisible /*up invis*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("Invisible");
			else if (amount > 0 && !m_IsInvisible /*down*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("Walk");
			else if (amount > 0 && m_IsInvisible /*down invis*/)
				GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("Invisible");

			GetGameObject()->Translate(0, amount, 0);
			m_CanMove = false;
		}
	}
}

void FygarCharacterComp::ExecuteMovement(Direction dir)
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
			(dir == Direction::left) ? MoveRight(-2) : MoveRight(2);
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

void FygarCharacterComp::FreezeForTime(float time)
{
	m_Freeze = true;
	m_FreezeTime = time;
}
