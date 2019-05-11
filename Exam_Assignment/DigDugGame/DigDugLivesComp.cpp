#include "pch.h"
#include "DigDugLivesComp.h"
#include "GameObject.h"
#include "QuadCollisionComponent.h"
#include "DigDugCharacterComp.h"
#include "Animator.h"

DigDugLivesComp::DigDugLivesComp(const std::string& texture, unsigned lives, MVector2_INT pos, bool reversed)
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
}

void DigDugLivesComp::Update()
{
	if (m_LostLive && !m_pGameObject->GetComponent<DigDugCharacterComp>()->GetIsFreeze())
	{
		m_pGameObject->GetComponent<Animator>()->SetActiveAnimation("Right");
		m_pGameObject->GetComponent<QuadCollisionComponent>()->Reset();
		m_pGameObject->SetPosition(0, 32, 0);
		m_LostLive = false;
	}
}

void DigDugLivesComp::FixedUpdate()
{
	if (!m_LostLive)
	{
		const auto comp = m_pGameObject->GetComponent<QuadCollisionComponent>();
		if (comp->CheckIfCollisionWith("Enemy", 5))
		{
			m_pGameObject->GetComponent<DigDugCharacterComp>()->FreezeForTime(1.2f);
			m_pGameObject->GetComponent<Animator>()->SetActiveAnimation("Dead");
			m_LostLive = true;
			if (m_Lives.size() > 0)
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
