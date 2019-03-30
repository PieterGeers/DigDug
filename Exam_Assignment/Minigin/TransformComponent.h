#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "BaseComponent.h"

class TransformComponent final : public BaseComponent
{
public:
	TransformComponent();
	virtual ~TransformComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

	const glm::vec3& GetPosition() const { return m_Position; }

	void SetPosition(float x, float y, float z);
	void Translate(float x, float y, float z);

private:
	glm::vec3 m_Position{0,0,0};

};

