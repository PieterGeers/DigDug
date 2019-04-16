#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "TextureRenderComponent.h"


CharacterComponent::CharacterComponent(std::shared_ptr<dae::GameObject>& character, Boundaries levelBounds, bool IsPlayer)
	:m_pCharacter(character)
	,m_Boundaries(levelBounds)
	,m_IsPlayer(IsPlayer)
{
}

void CharacterComponent::Update()
{
}

void CharacterComponent::FixedUpdate()
{
	if (!m_CanMove)
		m_CanMove = true;
}

void CharacterComponent::MoveRight(float amount)
{
	if (m_CanMove)
	{
		if (amount < 0 && m_pCharacter->GetTransform()->GetPosition().x > m_Boundaries.left ||
			amount > 0 && m_pCharacter->GetTransform()->GetPosition().x < m_Boundaries.right)
		{
			if (amount < 0 && !m_IsDigging && !m_Sprite[2] /*left*/)
			{
				ResetBitSet();
				m_Sprite[2] = true;
				m_pCharacter->GetComponent<TextureRenderComponent>()->SetSpritePosition(1, 0, 0, 1);
			}
			else if (amount < 0 && m_IsDigging && !m_Sprite[6] /*left dig*/)
			{
				ResetBitSet();
				m_Sprite[6] = true;
				m_pCharacter->GetComponent<TextureRenderComponent>()->SetSpritePosition(1, 2, 0, 1);
			}
			else if (amount > 0 && !m_IsDigging && !m_Sprite[3] /*right*/)
			{
				ResetBitSet();
				m_Sprite[3] = true;
				m_pCharacter->GetComponent<TextureRenderComponent>()->SetSpritePosition(0, 0, 0, 1);
			}
			else if (amount > 0 && m_IsDigging && !m_Sprite[7] /*right dig*/)
			{
				ResetBitSet();
				m_Sprite[7] = true;
				m_pCharacter->GetComponent<TextureRenderComponent>()->SetSpritePosition(0, 2, 0, 1);
			}
			m_pCharacter->Translate(amount, 0, 0);
			m_CanMove = false;
		}
	}
}

void CharacterComponent::MoveUp(float amount)
{
	if (m_CanMove)
	{
		if (amount < 0 && m_pCharacter->GetTransform()->GetPosition().y > m_Boundaries.top ||
			amount > 0 && m_pCharacter->GetTransform()->GetPosition().y < m_Boundaries.bottom)
		{
			if (amount < 0 && !m_IsDigging && !m_Sprite[0] /*up*/)
			{
				const int row = (m_Sprite[2]) ? 4 : 5;
				ResetBitSet();
				m_Sprite[0] = true;
				m_pCharacter->GetComponent<TextureRenderComponent>()->SetSpritePosition(row, 0, 0, 1);
			}
			else if (amount < 0 && m_IsDigging && !m_Sprite[4] /*up dig*/)
			{
				const int row = (m_Sprite[6]) ? 4 : 5;
				ResetBitSet();
				m_Sprite[4] = true;
				m_pCharacter->GetComponent<TextureRenderComponent>()->SetSpritePosition(row, 2, 0, 1);
			}
			else if (amount > 0 && !m_IsDigging && !m_Sprite[1] /*down*/)
			{
				const int row = (m_Sprite[3]) ? 2 : 3;
				ResetBitSet();
				m_Sprite[1] = true;
				m_pCharacter->GetComponent<TextureRenderComponent>()->SetSpritePosition(row, 0, 0, 1);
			}
			else if (amount > 0 && m_IsDigging && !m_Sprite[5] /*down dig*/)
			{
				const int row = (m_Sprite[7]) ? 2 : 3;
				ResetBitSet();
				m_Sprite[5] = true;
				m_pCharacter->GetComponent<TextureRenderComponent>()->SetSpritePosition(row, 2, 0, 1);
			}
			m_pCharacter->Translate(0, amount, 0);
			m_CanMove = false;
		}
	}
}

void CharacterComponent::ResetBounds(Boundaries levelBounds)
{
	m_Boundaries = levelBounds;
}

void CharacterComponent::ResetBitSet()
{
	for (unsigned int i = 0; i < m_Sprite.size(); ++i)
		m_Sprite[i] = false;
}