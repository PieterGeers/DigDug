#include "MiniginPCH.h"
#include "TransformComponent.h"


TransformComponent::TransformComponent()
{
}

void TransformComponent::Update()
{
}

void TransformComponent::FixedUpdate()
{
}

void TransformComponent::Render()
{
}

void TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
}

void TransformComponent::Translate(float x, float y, float z)
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}


