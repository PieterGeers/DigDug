#include "MiniginPCH.h"
#include "GameObject.h"


dae::GameObject::~GameObject() = default;

void dae::GameObject::Translate(float x, float y, float z) const
{
	m_Transform->Translate(x, y, z);
	SetComponentTransform();
}

void dae::GameObject::SetPosition(float x, float y, float z) const
{
	m_Transform->SetPosition(x, y, z);
	SetComponentTransform();
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> pComp)
{
	m_pComponents.push_back(pComp);
}

void dae::GameObject::SetComponentTransform() const
{
	for (auto element : m_pComponents)
	{
		element->SetTransform(m_Transform->GetPosition().x, m_Transform->GetPosition().y, m_Transform->GetPosition().z);
	}
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