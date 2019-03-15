#include "MiniginPCH.h"
#include "GameObject.h"


dae::GameObject::~GameObject() = default;

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> pComp)
{
	m_pComponents.push_back(pComp);
}

void dae::GameObject::Update()
{
	for (auto element : m_pComponents)
	{
		element->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (auto element : m_pComponents)
	{
		element->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (auto element : m_pComponents)
	{
		element->Render();
	}
}

