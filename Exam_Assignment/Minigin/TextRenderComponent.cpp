#include "MiniginPCH.h"
#include "TextRenderComponent.h"
#include "Renderer.h"


TextRenderComponent::TextRenderComponent(const std::string& text, std::shared_ptr<dae::Font> font, SDL_Color color, bool update)
	:m_Text(text)
	, m_Font(font)
	, m_Texture(nullptr)
	, m_NeedsUpdate(update)
	, m_Color(color)
{
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

	SDL_FreeSurface(surf);
	m_Texture = std::make_shared<dae::Texture2D>(texture);
}

void TextRenderComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

		SDL_FreeSurface(surf);

		m_Texture = std::make_shared<dae::Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextRenderComponent::FixedUpdate()
{
}

void TextRenderComponent::Render()
{
	if (m_Texture != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_X, m_Y);
	}
}

void TextRenderComponent::SetTransform(float x, float y, float)
{
	m_X = x;
	m_Y = y;
}

void TextRenderComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextRenderComponent::ChangeColor(const SDL_Color& color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}
