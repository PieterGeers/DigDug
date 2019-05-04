#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "TextureRenderComponent.h"

class DigDugWeaponComp final : public BaseComponent
{
public:
	DigDugWeaponComp(const std::string& texture, int rows, int cols, int size);
	~DigDugWeaponComp() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

	void AttackDigDug(Direction dir);
	void AttackFygar(Direction dir);

private:
	MVector2_INT scale{1,1};
	bool m_IsActive = false;
	float m_ActiveTime = 0.2f;
	std::shared_ptr<TextureRenderComponent> m_WeaponTexture;
};

