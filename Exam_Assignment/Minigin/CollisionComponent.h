#pragma once
#include "BaseComponent.h"

class CollisionComponent final : public BaseComponent
{
public:
	CollisionComponent();
	virtual ~CollisionComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

private:
	 
};

