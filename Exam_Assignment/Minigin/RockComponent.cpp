#include "MiniginPCH.h"
#include "RockComponent.h"


RockComponent::RockComponent(std::shared_ptr<dae::GameObject>& rock, Cell& cellUnderneath,
	const std::string& texturePath)
	:m_pRock(rock)
	,m_CellUnderneath(cellUnderneath)
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
		m_pRock->Translate(0, 4, 0);
		if (int(m_pRock->GetTransform()->GetPosition().y) >= m_EndFallPosition)
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
	const int fallDepth = amount * (m_CellUnderneath.posY - int(m_pRock->GetTransform()->GetPosition().y));
	m_EndFallPosition = int(m_pRock->GetTransform()->GetPosition().y) + fallDepth;
}


