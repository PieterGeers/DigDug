#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"

class TextRenderComponent final : public BaseComponent
{
public:
	explicit TextRenderComponent(const std::string& text, std::shared_ptr<dae::Font> font, SDL_Color color = SDL_Color{ 255,255,255,255 }, bool update = false);
	virtual ~TextRenderComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

	void SetText(const std::string& text);

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<dae::Font> m_Font;
	std::shared_ptr<dae::Texture2D> m_Texture;
	SDL_Color m_Color;
	float m_X = 0.0f, m_Y = 0.0f;
};

