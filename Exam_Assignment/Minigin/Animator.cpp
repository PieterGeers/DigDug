#include "MiniginPCH.h"
#include "Animator.h"
#include <algorithm>
#include "TextureRenderComponent.h"
#include "Debug.h"

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
	if (GetGameObject() == nullptr)
	{
		Debug::LogError("Animator component was not added to a valid GameObject");
		return;
	}
	const auto it = m_Animation.find(std::move(name));
	if (it == m_Animation.end())
	{
		Debug::LogWarning("Animation::SetActiveAnimation : Could not set animation because no animation was found with the name :" + name);
		return;
	}
	const auto comp = GetGameObject()->GetComponent<TextureRenderComponent>();
	if (comp != nullptr)
		comp->SetSpritePosition(*it->second);
	else
		Debug::LogError("Cannot set animation " + name + " -> no TextureRenderComponent was found on the GameObject");
}

void Animator::SetActiveAnimation(const std::string& name, const std::shared_ptr<TextureRenderComponent>& comp)
{
	const auto it = m_Animation.find(std::move(name));
	if (it == m_Animation.end())
	{
		Debug::LogWarning("Animation::SetActiveAnimation : Could not set animation because no animation was found with the name :" + name);
		return;
	}
	comp->SetSpritePosition(*(*it).second);
}

