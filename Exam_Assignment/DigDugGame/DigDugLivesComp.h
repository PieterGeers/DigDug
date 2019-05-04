#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "TextureRenderComponent.h"

class DigDugLivesComp final : public BaseComponent
{
public:
	DigDugLivesComp(const std::string& texture, unsigned lives, MVector2_INT pos, bool reversed = false);
	~DigDugLivesComp() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

private:
	std::vector<std::shared_ptr<TextureRenderComponent>> m_Lives;
	bool reset = false;
};

