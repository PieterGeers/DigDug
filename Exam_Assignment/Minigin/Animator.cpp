#include "MiniginPCH.h"
#include "Animator.h"
#include <algorithm>
#include "TextureRenderComponent.h"

Animator::Animator()
{
}

void Animator::AddAnimation(const std::shared_ptr<Animation>& animation)
{
	m_Animation.insert({ animation->name, animation });
}

void Animator::AddAnimation(const std::vector<std::shared_ptr<Animation>>& animationSet)
{
	std::for_each(animationSet.begin(), animationSet.end(), [&](const std::shared_ptr<Animation>& a) {m_Animation.insert({ a->name, a }); });
}

void Animator::SetActiveAnimation(const std::string& name)
{
	const auto it = m_Animation.find(std::move(name));
	if (it == m_Animation.end())
		return;
	GetGameObject()->GetComponent<TextureRenderComponent>()->SetSpritePosition(*(*it).second);

}

