#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameTime.h"
#include <SDL.h>
#include "TextRenderComponent.h"
#include "Renderer.h"

FPSComponent::FPSComponent(std::shared_ptr<dae::Font> font, SDL_Color color)
{
	m_TextRenderComp = std::make_shared<TextRenderComponent>("0 FPS", font, color, false);
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

		m_TextRenderComp->SetText(std::to_string(m_FpsCount) + " FPS");
		m_TextRenderComp->Update();
	}

}

void FPSComponent::FixedUpdate() {}

void FPSComponent::Render()
{
	m_TextRenderComp->Render();
}

void FPSComponent::SetTransform(float x, float y, float z)
{
	m_TextRenderComp->SetTransform(x, y, z);
}
