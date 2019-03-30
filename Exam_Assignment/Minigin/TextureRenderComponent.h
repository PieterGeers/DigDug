#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

class TextureRenderComponent final : public BaseComponent 
{
public:
	TextureRenderComponent(std::string path);
	TextureRenderComponent(std::string path, int tRows, int tColums, int scale = 1);
	virtual ~TextureRenderComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

	void SetSpritePosition(int row, int col, int rowOffset, int colOffset);

private:
	std::shared_ptr<dae::Texture2D> m_Texture;
	float m_X = 0.0f, m_Y = 0.0f, m_Acctime = 0.0f;
	int m_Columns = 1, m_Rows = 1, m_CurrentRow = 0, m_CurrentColumn = 0, m_RowOffset = 0, m_ColumnOffset = 0, m_StartRow = 0, m_StartColumn = 0, m_Scale = 1;
	bool m_IsSprite;
};

