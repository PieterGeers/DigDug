#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

BaseComponent::BaseComponent(): m_pGameObject(nullptr)
{
}

std::shared_ptr<TransformComponent> BaseComponent::GetTransform() const
{
	return m_pGameObject->GetTransform();
}
