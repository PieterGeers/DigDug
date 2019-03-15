#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameTime.h"
#include <SDL.h>
#include "Texture2D.h"
#include "TextRenderComponent.h"
#include "Renderer.h"

FPSComponent::FPSComponent(std::shared_ptr<dae::Font> font, SDL_Color color)
	:m_Color(color)
	,m_Font(font)
	,m_Texture(nullptr)
{
	std::string text = std::to_string(m_FpsCount) + " FPS";
	const auto surf = TTF_RenderText_Blended(font->GetFont(), text.c_str(), color);
	if (surf == nullptr)
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

	SDL_FreeSurface(surf);
	m_Texture = std::make_shared<dae::Texture2D>(texture);
}

void FPSComponent::Update()
{
	m_AccTime += dae::GameTime::GetInstance().DeltaT();
	++m_Fps;
	if (m_AccTime >= 1.0f)
	{
		m_AccTime -= 1.0f;
		m_FpsCount = m_Fps;
		m_Fps = 0;

		std::string text = std::to_string(m_FpsCount) + " FPS";
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), text.c_str(), m_Color);
		if (surf == nullptr)
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<dae::Texture2D>(texture);
	}

}

void FPSComponent::FixedUpdate(){}

void FPSComponent::Render()
{
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_X, m_Y);
}

void FPSComponent::SetPosition(float x, float y)
{
	m_X = x;
	m_Y = y;
}
