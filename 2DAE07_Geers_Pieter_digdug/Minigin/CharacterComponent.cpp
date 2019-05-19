#include "MiniginPCH.h"
#include "CharacterComponent.h"

CharacterComponent::CharacterComponent(Boundaries levelBounds)
	:m_Boundaries(levelBounds)
{
}

void CharacterComponent::Update()
{}

void CharacterComponent::FixedUpdate()
{}

void CharacterComponent::MoveRight(float)
{}

void CharacterComponent::MoveUp(float)
{}

void CharacterComponent::ResetBounds(Boundaries levelBounds)
{
	m_Boundaries = levelBounds;
}

