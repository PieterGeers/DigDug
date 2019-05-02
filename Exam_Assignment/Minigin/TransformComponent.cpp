#include "MiniginPCH.h"
#include "TransformComponent.h"


dae::TransformComponent::TransformComponent()
{
}

void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::FixedUpdate()
{
}

void dae::TransformComponent::Render()
{
}

void dae::TransformComponent::SetTransform(float, float, float)
{}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
}

void dae::TransformComponent::Translate(float x, float y, float z)
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}


