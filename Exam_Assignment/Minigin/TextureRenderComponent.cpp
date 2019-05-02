#include "MiniginPCH.h"
#include "TextureRenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameTime.h"


TextureRenderComponent::TextureRenderComponent(const std::shared_ptr<dae::Texture2D>& text)
	:m_IsSprite(false)
	, m_Texture(std::move(text))
{
}

TextureRenderComponent::TextureRenderComponent(std::string path)
	:m_IsSprite(false)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(path);
}

TextureRenderComponent::TextureRenderComponent(std::string path, int tRows, int tColumns, int scale)
	: m_IsSprite(true)
	, m_Scale(scale)
{
	m_Rows = tRows;
	m_Columns = tColumns;
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(path);
}

void TextureRenderComponent::Update()
{
	if (m_IsSprite)
	{
		m_Acctime += dae::GameTime::GetInstance().DeltaT();
		if (m_Acctime > 0.2f)
		{
			m_Acctime -= 0.2f;
			++m_CurrentColumn;
			if (m_CurrentColumn > m_StartColumn + m_ColumnOffset)
			{
				m_CurrentColumn = m_StartColumn;
				if (m_RowOffset > 0)
				{
					++m_CurrentRow;
					if (m_CurrentRow > m_StartRow + m_RowOffset)
					{
						m_CurrentRow = m_StartRow;
					}
				}
			}
		}
	}
}

void TextureRenderComponent::FixedUpdate()
{
}

void TextureRenderComponent::Render()
{
	if (m_Texture != nullptr)
	{
		if (!m_IsSprite)
			dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_X, m_Y, static_cast<float>(m_Texture->GetWidth())* m_Scale, static_cast<float>(m_Texture->GetHeight())*m_Scale);
		else
			dae::Renderer::GetInstance().RenderTexture(*m_Texture, SDL_Rect{ int(m_X), int(m_Y), m_Texture->GetWidth() / m_Columns * m_Scale, m_Texture->GetHeight() / m_Rows * m_Scale },
				SDL_Rect{ m_CurrentColumn*(m_Texture->GetWidth() / m_Columns), m_CurrentRow*(m_Texture->GetHeight() / m_Rows), m_Texture->GetWidth() / m_Columns , m_Texture->GetHeight() / m_Rows });
	}
}

void TextureRenderComponent::SetTransform(float x, float y, float)
{
	m_X = x;
	m_Y = y;
}

void TextureRenderComponent::SetSpritePosition(Animation info)
{
	if (m_ActiveAnimation == info.name)
		return;
	m_ActiveAnimation = info.name;
	m_CurrentRow = info.info.startRow;
	m_CurrentColumn = info.info.startColumn;
	m_ColumnOffset = info.info.ColumnOffset;
	m_RowOffset = info.info.RowOffset;
	m_StartColumn = info.info.startColumn;
	m_StartRow = info.info.startRow;
}

void TextureRenderComponent::SetSpritePosition(unsigned startRow, unsigned startColumn, unsigned rowOffset,
	unsigned columnOffset)
{
	m_CurrentRow = startRow;
	m_CurrentColumn = startColumn;
	m_ColumnOffset = columnOffset;
	m_RowOffset = rowOffset;
	m_StartColumn = startColumn;
	m_StartRow = startRow;

}


