#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "TextureRenderComponent.h"

class DigDugLivesComp final : public BaseComponent
{
public:
	DigDugLivesComp(const std::string& texture, unsigned lives, MVector2_INT resetPos, MVector2_INT pos, bool reversed = false, bool canCollideWithEnemy = true);
	~DigDugLivesComp() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

	unsigned GetNumberOfLives() const { return unsigned(m_Lives.size()); }
	void HealthLost();

private:
	std::vector<std::shared_ptr<TextureRenderComponent>> m_Lives;
	bool m_LostLive = false;
	MVector2_INT m_ResetPos{0,0};
	bool m_CanCollideWithEnemy = true;
};

