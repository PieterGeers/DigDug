#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <unordered_map>

class QuadCollisionComponent final : public BaseComponent
{
public:
	QuadCollisionComponent(MVector2_INT TopLeft, int size, const std::string& tag);
	QuadCollisionComponent(MVector2_INT TopLeft, int width, int height, const std::string& tag);

	~QuadCollisionComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

	static void HandleQuadCollision();
	static bool IsQuadColliding(M_Rectangle one, M_Rectangle other);

	void SetIsColliding() { m_IsColliding = true; }
	void AddIsCollidingWith(const std::string& tag) { m_ColliderTags.push_back(std::move(tag)); }
	void Reset() { m_IsColliding = false; m_ColliderTags.clear(); }

	void SetIsActive(bool isActive) { m_IsActive = isActive; }

	bool GetIsColliding() const { return m_IsColliding; }
	std::vector<std::string> GetColliderTags() const { return m_ColliderTags; }
	bool CheckIfCollisionWith(const std::string& checkWith, unsigned nbOfCharsToCheck);

protected:
	M_Rectangle m_Rectangle;
	bool m_IsActive = true;
private:
	int width, height;
	static std::unordered_map<std::string, QuadCollisionComponent*> m_CollisionObjects;
	bool m_IsColliding = false;
	std::vector<std::string> m_ColliderTags;
};

