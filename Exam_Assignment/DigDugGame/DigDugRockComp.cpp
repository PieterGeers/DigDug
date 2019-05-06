#include "pch.h"
#include "DigDugRockComp.h"
#include "TransformComponent.h"

DigDugRockComp::DigDugRockComp(DigDugCell& cellUnderneath,
	const std::string& texturePath)
	: m_CellUnderneath(cellUnderneath)
	, m_EndFallPosition(0)
{
	m_Texture = std::make_shared<TextureRenderComponent>(texturePath);
}

void DigDugRockComp::Update()
{
}

void DigDugRockComp::FixedUpdate()
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

void DigDugRockComp::Render()
{
	if (m_IsActive)
		m_Texture->Render();
}

void DigDugRockComp::SetTransform(float x, float y, float z)
{
	m_Texture->SetTransform(x, y, z);
}

void DigDugRockComp::FallForAmountCell(unsigned amount)
{
	m_IsFalling = true;
	const int fallDepth = amount * (m_CellUnderneath.position.y - int(GetTransform()->GetPosition().y));
	m_EndFallPosition = int(GetTransform()->GetPosition().y) + fallDepth;
}


