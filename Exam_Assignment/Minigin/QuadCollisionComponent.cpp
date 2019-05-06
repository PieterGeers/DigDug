#include "MiniginPCH.h"
#include "QuadCollisionComponent.h"
#include "Debug.h"

std::unordered_map<std::string, QuadCollisionComponent*> QuadCollisionComponent::m_CollisionObjects;

QuadCollisionComponent::QuadCollisionComponent(MVector2_INT TopLeft, int size, const std::string& tag)
	:width(size),height(size)
{
	m_Rectangle.TopLeft = TopLeft;
	m_Rectangle.BottomRight = MVector2_INT(TopLeft.x + size, TopLeft.y + size);

	const auto find = m_CollisionObjects.find(tag);
	if (find != m_CollisionObjects.end())
		Debug::LogError("QuadCollisionComponent with tag <" + tag + "> already exists");
	m_CollisionObjects.insert({ tag, this });
}

QuadCollisionComponent::QuadCollisionComponent(MVector2_INT TopLeft, int width, int height, const std::string& tag)
	:width(width),height(height)
{
	m_Rectangle.TopLeft = TopLeft;
	m_Rectangle.BottomRight = MVector2_INT(TopLeft.x + width, TopLeft.y + height);

	const auto find = m_CollisionObjects.find(tag);
	if (find != m_CollisionObjects.end())
		Debug::LogError("QuadCollisionComponent with tag <" + tag + "> already exists");
	m_CollisionObjects.insert({ tag ,this });
}

void QuadCollisionComponent::Update()
{
}

void QuadCollisionComponent::FixedUpdate()
{
}

void QuadCollisionComponent::Render()
{
}

void QuadCollisionComponent::SetTransform(float x, float y, float)
{
	m_Rectangle.TopLeft = MVector2_INT(static_cast<int>(x),static_cast<int>(y));
	m_Rectangle.BottomRight = MVector2_INT(static_cast<int>(x) + width, static_cast<int>(y) + height);
}

void QuadCollisionComponent::HandleQuadCollision()
{
	for (auto i =m_CollisionObjects.begin(); i != m_CollisionObjects.end(); ++i)
	{
		if (!i->second->m_IsActive)
			continue;
		i->second->Reset();
		for (auto j = m_CollisionObjects.begin(); j != m_CollisionObjects.end();++j)
		{
			if (!j->second->m_IsActive)
				continue;
			if (i->first != j->first && IsQuadColliding(i->second->m_Rectangle, j->second->m_Rectangle))
			{
				i->second->SetIsColliding();
				i->second->AddIsCollidingWith(j->first);
			}
		}
	}
}

bool QuadCollisionComponent::IsQuadColliding(M_Rectangle one, M_Rectangle other)
{
	if (one.TopLeft.x >= other.BottomRight.x || 
		other.TopLeft.x >= one.BottomRight.x)
		return false;
	if (one.TopLeft.y >= other.BottomRight.y || 
		other.TopLeft.y >= one.BottomRight.y)
		return false;
	return true;
}

bool QuadCollisionComponent::CheckIfCollisionWith(const std::string& checkWith, unsigned nbOfCharsToCheck)
{
	if (m_IsColliding)
	{
		for (auto tag : m_ColliderTags)
		{
			if (Debug::CompareStringLeft(tag, checkWith, nbOfCharsToCheck))
			{
				return true;
			}
		}
	}
	return false;
}
