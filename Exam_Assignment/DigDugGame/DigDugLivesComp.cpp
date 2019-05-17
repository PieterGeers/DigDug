#include "pch.h"
#include "DigDugLivesComp.h"
#include "GameObject.h"
#include "QuadCollisionComponent.h"
#include "DigDugCharacterComp.h"
#include "Animator.h"
#include "ServiceLocator.h"
#include "FygarCharacterComp.h"
#include "Score.h"

DigDugLivesComp::DigDugLivesComp(const std::string& texture, unsigned lives,MVector2_INT resetPos , MVector2_INT pos, bool reversed, bool canCollideWithEnemy)
{
	for (unsigned i = 0; i < lives; ++i)
	{
		std::shared_ptr<TextureRenderComponent> T = std::make_shared<TextureRenderComponent>(texture);
		m_Lives.push_back(T);
		if (reversed)
			m_Lives[i]->SetTransform(static_cast<float>(pos.x - (i* T->GetWidth())), static_cast<float>(pos.y), 0);
		else
			m_Lives[i]->SetTransform(static_cast<float>(pos.x + (i* T->GetWidth())), static_cast<float>(pos.y), 0);
	}
	m_ResetPos = resetPos;
	m_CanCollideWithEnemy = canCollideWithEnemy;
}

void DigDugLivesComp::Update()
{
	if (m_CanCollideWithEnemy)
	{
		if (m_LostLive && !m_pGameObject->GetComponent<DigDugCharacterComp>()->GetIsFreeze())
		{
			m_pGameObject->GetComponent<Animator>()->SetActiveAnimation("Right");
			m_pGameObject->GetComponent<QuadCollisionComponent>()->Reset();
			m_pGameObject->SetPosition(static_cast<float>(m_ResetPos.x), static_cast<float>(m_ResetPos.y), 0);
			m_LostLive = false;
		}
	}
	else if (!m_CanCollideWithEnemy)
	{
		if (m_LostLive && !m_pGameObject->GetComponent<FygarCharacterComp>()->GetIsFreeze())
		{
			m_pGameObject->GetComponent<Animator>()->SetActiveAnimation("Walk");
			m_pGameObject->GetComponent<QuadCollisionComponent>()->Reset();
			m_pGameObject->SetPosition(static_cast<float>(m_ResetPos.x), static_cast<float>(m_ResetPos.y), 0);
			m_LostLive = false;
		}
	}
}

void DigDugLivesComp::FixedUpdate()
{
	if (!m_LostLive && m_CanCollideWithEnemy)
	{
		const auto comp = m_pGameObject->GetComponent<QuadCollisionComponent>();
		if (comp->CheckIfCollisionWith("Enemy", 5))
		{
			m_pGameObject->GetComponent<DigDugCharacterComp>()->FreezeForTime(1.2f);
			m_pGameObject->GetComponent<Animator>()->SetActiveAnimation("Dead");
			m_LostLive = true;
			if (m_Lives.size() > 0)
				m_Lives.pop_back();
			if (m_Lives.size() == 0)
			{
				std::string tag = m_pGameObject->GetComponent<QuadCollisionComponent>()->GetTag();
				auto it = QuadCollisionComponent::GetCollisionObjects().find(tag);
				QuadCollisionComponent::GetCollisionObjects().erase(it);
				m_pGameObject->GetComponent<DigDugCharacterComp>()->SetDead();
				m_pGameObject->GetComponent<TextureRenderComponent>()->StopRender();
				int idx = m_pGameObject->GetComponent<DigDugCharacterComp>()->GetIndex();
				ServiceLocator::GetPlayers().erase(ServiceLocator::GetPlayers().find(idx));
			}
		}
	}
	if (!m_LostLive && !m_CanCollideWithEnemy)
	{
		if (!m_pGameObject->GetComponent<FygarCharacterComp>()->GetIsPlayerInvisible())
		{
			auto collision = GetGameObject()->GetComponent<QuadCollisionComponent>();
			auto tags = collision->GetColliderTags();
			for (auto t : tags)
			{
				if (Debug::CompareStringLeft(t, "Attack", 6))
				{
					m_pGameObject->GetComponent<FygarCharacterComp>()->FreezeForTime(.8f);
					m_pGameObject->GetComponent<Animator>()->SetActiveAnimation("Explode");
					m_LostLive = true;
					Score::GetInstance().AddScore(2500);
					if (ServiceLocator::GetAgents().size() == 0 && m_Lives.size() > 0)
						m_Lives.pop_back();
					if (m_Lives.size() == 0)
					{
						std::string tag = m_pGameObject->GetComponent<QuadCollisionComponent>()->GetTag();
						auto it = QuadCollisionComponent::GetCollisionObjects().find(tag);
						QuadCollisionComponent::GetCollisionObjects().erase(it);
						m_pGameObject->GetComponent<FygarCharacterComp>()->SetDead();
						//m_pGameObject->GetComponent<TextureRenderComponent>()->StopRender();
					}
				}
			}
		}
		if (ServiceLocator::GetAgents().size() +1 < m_Lives.size())
		{
			m_Lives.pop_back();
		}
	}
}

void DigDugLivesComp::Render()
{
	for (auto T : m_Lives)
	{
		T->Render();
	}
}

void DigDugLivesComp::SetTransform(float, float, float)
{
}
