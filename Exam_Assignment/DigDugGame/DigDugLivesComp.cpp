#include "pch.h"
#include "DigDugLivesComp.h"
#include "GameObject.h"
#include "QuadCollisionComponent.h"
#include "Debug.h"

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
}

void DigDugLivesComp::FixedUpdate()
{
	const auto comp = m_pGameObject->GetComponent<QuadCollisionComponent>();
	if (comp->GetIsColliding())
	{
		if (reset)
			return;
		auto tags = comp->GetColliderTags();
		for (auto tag : tags)
		{
			if (Debug::CompareStringLeft(tag, "Rock", 4))
			{
				reset = true;
				m_Lives.pop_back();
				return;
			}
		}
	}
	else
		reset = false;
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
