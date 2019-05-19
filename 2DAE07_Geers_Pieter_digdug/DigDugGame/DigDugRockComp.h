#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "TextureRenderComponent.h"
#include "DigDugStructs.h"

class DigDugRockComp final : public BaseComponent
{
public:
	DigDugRockComp(DigDugCell& cellUnderneath, const std::string& texturePath);
	~DigDugRockComp() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

	const std::shared_ptr<TextureRenderComponent>& GetTexture() const { return m_Texture; }
	const DigDugCell& GetCell() const { return m_CellUnderneath; }
	void FallForAmountCell(unsigned amount);
	bool IsRockActive() const { return m_IsActive; }
	bool IsFalling() const { return m_IsFalling; }

private:
	DigDugCell& m_CellUnderneath;
	bool m_IsFalling = false, m_IsActive = true;
	std::shared_ptr<TextureRenderComponent> m_Texture;
	int m_EndFallPosition;
};

