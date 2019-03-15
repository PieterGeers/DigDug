#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

class TextureRenderComponent final : public BaseComponent 
{
public:
	TextureRenderComponent(std::string path);
	virtual ~TextureRenderComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;

	void SetPosition(float x, float y);

private:
	std::shared_ptr<dae::Texture2D> m_Texture;
	float m_X = 0.0f, m_Y = 0.0f;
};

