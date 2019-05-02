#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "TextRenderComponent.h"

class FPSComponent final : public BaseComponent
{
public:
	FPSComponent(std::shared_ptr<dae::Font> font, SDL_Color color = SDL_Color{ 255,255,255,255 });
	~FPSComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

private:
	float m_AccTime = 0.0f;
	int m_Fps = 0;
	int m_FpsCount = 0;
	std::shared_ptr<TextRenderComponent> m_TextRenderComp;

};

