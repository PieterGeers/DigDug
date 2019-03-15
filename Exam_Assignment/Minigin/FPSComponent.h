#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Font.h"

class FPSComponent final : public BaseComponent
{
public:
	FPSComponent(std::shared_ptr<dae::Font> font, SDL_Color color = SDL_Color{ 255,255,255,255 });
	virtual ~FPSComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;

	void SetPosition(float x, float y);

private:
	float m_AccTime = 0.0f, m_X = 0.0f, m_Y = 0.0f;
	int m_Fps = 0;
	int m_FpsCount = 0;
	std::shared_ptr<dae::Font> m_Font;
	std::shared_ptr<dae::Texture2D> m_Texture;
	SDL_Color m_Color;
};

