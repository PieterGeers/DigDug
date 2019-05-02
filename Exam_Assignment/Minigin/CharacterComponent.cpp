#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "TextureRenderComponent.h"
#include <algorithm>


CharacterComponent::CharacterComponent(std::shared_ptr<dae::GameObject>& character, Boundaries levelBounds)
	:m_pCharacter(character)
	,m_Boundaries(levelBounds)
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

void CharacterComponent::AddAnimation(const std::shared_ptr<Animation>& animation)
{
	m_Animation.insert({ animation->name, animation });
}

void CharacterComponent::AddAnimation(const std::vector<std::shared_ptr<Animation>>& animationSet)
{
	std::for_each(animationSet.begin(), animationSet.end(), [&](const std::shared_ptr<Animation>& a) {m_Animation.insert({ a->name, a }); });
}

void CharacterComponent::SetActiveAnimation(const std::string& name)
{
	const auto component = m_pCharacter->GetComponent<TextureRenderComponent>();
	if (component == nullptr)
		return;
	const auto it = m_Animation.find(std::move(name));
	if (it == m_Animation.end())
		return;
	component->SetSpritePosition(*(*it).second);
}

