#include "MiniginPCH.h"
#include "WeaponComponent.h"
#include "GameTime.h"


WeaponComponent::WeaponComponent(std::shared_ptr<dae::GameObject>& character, const std::string& textPath, int rows, int column, int scale, bool isPlayer)
	:m_IsPlayer(isPlayer)
	,m_IsActive(false)
	,m_Character(character)
	,m_ActiveTime(0.0f)
{
	m_WeaponTexture = std::make_shared<TextureRenderComponent>(textPath, rows, column, scale);
}

void WeaponComponent::Update()
{
	m_WeaponTexture->Update();
	if (m_IsActive)
	{
		m_ActiveTime -= dae::GameTime::GetInstance().DeltaT();
		if (m_ActiveTime < 0.0f)
		{
			m_IsActive = false;
		}
	}
}

void WeaponComponent::FixedUpdate()
{
	if (m_IsActive)
	{
		if (m_IsPlayer)
		{
			const auto component = m_Character->GetComponent<CharacterComponent>();
			const auto transform = m_Character->GetTransform();
			const auto width = m_Character->GetComponent<TextureRenderComponent>()->GetSpriteWidth();
			const auto height = m_Character->GetComponent<TextureRenderComponent>()->GetSpriteHeight();
			if (component == nullptr)
				return;
			switch (component->GetCurrentDirection())
			{
			case up:
				m_WeaponTexture->SetTransform(transform->GetPosition().x, transform->GetPosition().y - height, transform->GetPosition().z);
				break;
			case down:
				m_WeaponTexture->SetTransform(transform->GetPosition().x, transform->GetPosition().y + height, transform->GetPosition().z);
				break;
			case left:
				m_WeaponTexture->SetTransform(transform->GetPosition().x - width, transform->GetPosition().y, transform->GetPosition().z);
				break;
			case right:
				m_WeaponTexture->SetTransform(transform->GetPosition().x + width, transform->GetPosition().y, transform->GetPosition().z);
				break;
			case none: break;
			default: ;
			}
		}
	}
}

void WeaponComponent::Render()
{
	if (m_IsActive)
		m_WeaponTexture->Render();
}

void WeaponComponent::SetTransform(float x, float y, float z)
{
	m_WeaponTexture->SetTransform(x, y, z);
}

void WeaponComponent::SetPosition(float, float, float)
{	
}

void WeaponComponent::SetActive(int startRow, int startColumn, int rowOffset, int columnOffset)
{
	m_IsActive = true;
	m_ActiveTime = 0.1f * (rowOffset + 1 * columnOffset + 1);
	m_WeaponTexture->SetSpritePosition(startRow, startColumn, rowOffset, columnOffset);
}

