#include "MiniginPCH.h"
#include "TextureRenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"


TextureRenderComponent::TextureRenderComponent(std::string path)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(path);
}

void TextureRenderComponent::Update()
{
}

void TextureRenderComponent::FixedUpdate()
{
}

void TextureRenderComponent::Render()
{
	if (m_Texture != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_X, m_Y);
	}
}

void TextureRenderComponent::SetPosition(float x, float y)
{
	m_X = x;
	m_Y = y;
}


