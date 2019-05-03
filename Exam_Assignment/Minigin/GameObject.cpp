#include "MiniginPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "Debug.h"


GameObject::~GameObject() = default;

void GameObject::Translate(float x, float y, float z) const
{
	m_Transform->Translate(x, y, z);
	SetComponentTransform();
}

void GameObject::SetPosition(float x, float y, float z) const
{
	m_Transform->SetPosition(x, y, z);
	SetComponentTransform();
}

void GameObject::AddComponent(std::shared_ptr<BaseComponent> pComp)
{
	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = this;
}

void GameObject::RemoveComponent(std::shared_ptr<BaseComponent> pComp)
{
	const auto comp = std::find(m_pComponents.begin(), m_pComponents.end(), pComp);
	if (comp == m_pComponents.end())
		return;
	if (typeid(*pComp) == typeid(TransformComponent))
		return;
	m_pComponents.erase(comp);
}

void GameObject::AddChild(const std::string& tag, std::shared_ptr<GameObject> child)
{
	const auto find = m_Children.find(tag);
	if (find != m_Children.end())
		Debug::LogError("GameObject::AddChild : GameObject with this tag already exists");
	m_Children.insert({ tag, child });
}

void GameObject::RemoveChild(const std::string& tag)
{
	const auto find = m_Children.find(tag);
	if (find == m_Children.end())
		Debug::LogError("GameObject::RemoveChild : GameObject with this tag could not be removed because the tag does not match");
	m_Children.erase(find);
}

void GameObject::SetComponentTransform() const
{
	for (auto element : m_pComponents)
	{
		element->SetTransform(m_Transform->GetPosition().x, m_Transform->GetPosition().y, m_Transform->GetPosition().z);
	}
}

void GameObject::Update()
{
	for (auto element : m_pComponents)
	{
		element->Update();
	}
}

void GameObject::FixedUpdate()
{
	for (auto element : m_pComponents)
	{
		element->FixedUpdate();
	}
}

void GameObject::Render() const
{
	for (auto element : m_pComponents)
	{
		element->Render();
	}
}