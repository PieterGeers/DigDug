#include "MiniginPCH.h"
#include "RockComponent.h"
#include "TransformComponent.h"

RockComponent::RockComponent(DigDugCell& cellUnderneath,
	const std::string& texturePath)
	: m_CellUnderneath(cellUnderneath)
	, m_EndFallPosition(0)
{
	m_Texture = std::make_shared<TextureRenderComponent>(texturePath);
}

void RockComponent::Update()
{
}

void RockComponent::FixedUpdate()
{
	if (m_IsActive && m_IsFalling)
	{
		GetGameObject()->Translate(0, 4, 0);
		if (int(GetTransform()->GetPosition().y) >= m_EndFallPosition)
		{
			m_IsFalling = false;
			m_IsActive = false;
		}
	}
}

void RockComponent::Render()
{
	if (m_IsActive)
		m_Texture->Render();
}

void RockComponent::SetTransform(float x, float y, float z)
{
	m_Texture->SetTransform(x, y, z);
}

void RockComponent::FallForAmountCell(unsigned amount)
{
	m_IsFalling = true;
	const int fallDepth = amount * (m_CellUnderneath.position.y - int(GetTransform()->GetPosition().y));
	m_EndFallPosition = int(GetTransform()->GetPosition().y) + fallDepth;
}


