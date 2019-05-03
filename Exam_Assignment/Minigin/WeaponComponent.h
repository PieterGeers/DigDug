#pragma once
#include "BaseComponent.h"
#include "TextureRenderComponent.h"
#include "CharacterComponent.h"

class WeaponComponent final : public BaseComponent
{
public:
	WeaponComponent(const std::string& textPath, int rows, int column, int scale, bool isPlayer = true);
	~WeaponComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;
	void SetPosition(float x, float y, float z);
	void SetActive(int startRow, int startColumn, int rowOffset, int columnOffset);

private:
	std::shared_ptr<TextureRenderComponent> m_WeaponTexture;
	Direction m_CurrentDirection = Direction::none;
	bool m_IsPlayer;
	bool m_IsActive;
	float m_ActiveTime;
};

