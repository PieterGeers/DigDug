#include "pch.h"
#include "DigDugWeaponComp.h"
#include "GameObject.h"
#include "Animator.h"
#include "GameTime.h"
#include "QuadCollisionComponent.h"

DigDugWeaponComp::DigDugWeaponComp(const std::string& texture, int rows, int cols, int size)
	:m_WeaponTexture(std::make_shared<TextureRenderComponent>(texture, rows, cols, size))
{}

DigDugWeaponComp::DigDugWeaponComp(const std::string& texture, int size)
	: m_WeaponTexture(std::make_shared<TextureRenderComponent>(texture, size))
{
}

void DigDugWeaponComp::Update()
{
	if (m_IsActive)
	{
		m_WeaponTexture->Update();
		m_ActiveTime -= dae::GameTime::GetInstance().DeltaT();
		if (!m_IsDigDug)
		{
			//change collisionbox
			if (m_Direction == left)
			{
				if (m_ActiveTime > 0.4f)
					m_pGameObject->GetComponent<QuadCollisionComponent>()->ChangeCollisionSize({ static_cast<int>(GetTransform()->GetPosition().x) - 32, static_cast<int>(GetTransform()->GetPosition().y) }, 32, 32);
				else if (m_ActiveTime > 0.2f)
					m_pGameObject->GetComponent<QuadCollisionComponent>()->ChangeCollisionSize({ static_cast<int>(GetTransform()->GetPosition().x) - 64, static_cast<int>(GetTransform()->GetPosition().y) }, 64, 32);
				else if (m_ActiveTime > 0.0f)
					m_pGameObject->GetComponent<QuadCollisionComponent>()->ChangeCollisionSize({ static_cast<int>(GetTransform()->GetPosition().x) - 96, static_cast<int>(GetTransform()->GetPosition().y) }, 96, 32);
			}
			else if (m_Direction == right)
			{
				if (m_ActiveTime > 0.4f)
					m_pGameObject->GetComponent<QuadCollisionComponent>()->ChangeCollisionSize({ static_cast<int>(GetTransform()->GetPosition().x)+32, static_cast<int>(GetTransform()->GetPosition().y) }, 32, 32);
				else if (m_ActiveTime > 0.2f)
					m_pGameObject->GetComponent<QuadCollisionComponent>()->ChangeCollisionSize({ static_cast<int>(GetTransform()->GetPosition().x)+32, static_cast<int>(GetTransform()->GetPosition().y) }, 64, 32);
				else if (m_ActiveTime > 0.0f)
					m_pGameObject->GetComponent<QuadCollisionComponent>()->ChangeCollisionSize({ static_cast<int>(GetTransform()->GetPosition().x)+32, static_cast<int>(GetTransform()->GetPosition().y) }, 96, 32);
			}
		}
		if (m_ActiveTime <= 0.0f)
		{
			m_IsActive = false;
			m_pGameObject->GetComponent<QuadCollisionComponent>()->SetIsActive(false);
		}
	}
}

void DigDugWeaponComp::FixedUpdate()
{
	if (m_IsActive)
		m_WeaponTexture->FixedUpdate();
}

void DigDugWeaponComp::Render()
{
	if (m_IsActive)
		m_WeaponTexture->Render();
}

void DigDugWeaponComp::SetTransform(float , float , float )
{}

void DigDugWeaponComp::AttackDigDug(Direction dir)
{
	if (!m_IsActive)
	{
		m_IsDigDug = true;
		m_ActiveTime = 0.2f;
		m_IsActive = true;
		const auto comp = m_pGameObject->GetComponent<Animator>();
		const auto coll = m_pGameObject->GetComponent<QuadCollisionComponent>();
		switch (dir)
		{
		case up:
			//comp->SetActiveAnimation("Up", m_WeaponTexture);
			m_WeaponTexture->SetAngle(270);
			m_WeaponTexture->SetTransform(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y - m_WeaponTexture->GetSpriteHeight(), GetTransform()->GetPosition().z);
			coll->SetTransform(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y - m_WeaponTexture->GetSpriteHeight(), GetTransform()->GetPosition().z);
			coll->SetIsActive(true);
			break;
		case down:
			//comp->SetActiveAnimation("Down", m_WeaponTexture);
			m_WeaponTexture->SetAngle(90);
			m_WeaponTexture->SetTransform(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y + m_WeaponTexture->GetSpriteHeight(), GetTransform()->GetPosition().z);
			coll->SetTransform(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y + 32, GetTransform()->GetPosition().z);
			coll->SetIsActive(true);
			break;
		case left:
			//comp->SetActiveAnimation("Left", m_WeaponTexture);
			m_WeaponTexture->SetAngle(180);
			m_WeaponTexture->SetTransform(GetTransform()->GetPosition().x - m_WeaponTexture->GetSpriteWidth(), GetTransform()->GetPosition().y, GetTransform()->GetPosition().z);
			coll->SetTransform(GetTransform()->GetPosition().x - m_WeaponTexture->GetSpriteWidth(), GetTransform()->GetPosition().y, GetTransform()->GetPosition().z);
			coll->SetIsActive(true);
			break;
		case right:
			//comp->SetActiveAnimation("Right", m_WeaponTexture);
			m_WeaponTexture->SetAngle(0);
			m_WeaponTexture->SetTransform(GetTransform()->GetPosition().x + m_WeaponTexture->GetSpriteWidth(), GetTransform()->GetPosition().y, GetTransform()->GetPosition().z);
			coll->SetTransform(GetTransform()->GetPosition().x + 32, GetTransform()->GetPosition().y, GetTransform()->GetPosition().z);
			coll->SetIsActive(true);
			break;
		case none: break;
		default:;
		}
	}
}

void DigDugWeaponComp::AttackFygar(Direction dir)
{
	if (!m_IsActive && (dir == Direction::left || dir == Direction::right))
	{
		m_IsDigDug = false;
		m_ActiveTime = 0.6f;
		m_IsActive = true;
		const auto comp = m_pGameObject->GetComponent<Animator>();
		const auto coll = m_pGameObject->GetComponent<QuadCollisionComponent>();
		switch (dir)
		{
		case up:break;
		case down:break;
		case left:
			m_Direction = left;
			comp->SetActiveAnimation("Left", m_WeaponTexture);
			m_WeaponTexture->SetTransform(GetTransform()->GetPosition().x - m_WeaponTexture->GetSpriteWidth(), GetTransform()->GetPosition().y, GetTransform()->GetPosition().z);
			coll->SetIsActive(true);
			coll->SetTransform(GetTransform()->GetPosition().x - m_WeaponTexture->GetSpriteWidth(), GetTransform()->GetPosition().y, GetTransform()->GetPosition().z);
			break;
		case right:
			m_Direction = right;
			m_WeaponTexture->SetTransform(GetTransform()->GetPosition().x + 32, GetTransform()->GetPosition().y, GetTransform()->GetPosition().z);
			comp->SetActiveAnimation("Right", m_WeaponTexture);
			coll->SetIsActive(true);
			coll->SetTransform(GetTransform()->GetPosition().x + 32, GetTransform()->GetPosition().y, GetTransform()->GetPosition().z);
			break;
		case none: break;
		default:;
		}
	}
}
