#include "MiniginPCH.h"
#include "ButtonComponent.h"

ButtonComponent::ButtonComponent(std::string text, std::shared_ptr<dae::Font> font, SDL_Color color, std::function<void()> function)
	:m_Color(color)
{
	m_Button = std::make_shared<TextRenderComponent>(text, font, color, false);
	m_Function = function;
}

void ButtonComponent::Update()
{
	m_Button->Update();
}

void ButtonComponent::FixedUpdate(){}

void ButtonComponent::Render()
{
	m_Button->Render();
}

void ButtonComponent::SetTransform(float x, float y, float z)
{
	m_Button->SetTransform(x, y, z);
}

void ButtonComponent::HooverOver(const SDL_Color& color) const
{
	m_Button->ChangeColor(color);
}

void ButtonComponent::ResetColor() const
{
	m_Button->ChangeColor(m_Color);
}
