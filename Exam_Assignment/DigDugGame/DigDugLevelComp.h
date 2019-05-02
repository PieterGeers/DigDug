#pragma once
#include "LevelComponent.h"
#include "TextureRenderComponent.h"

class DigDugLevelComp final : public LevelComponent
{
public:
	DigDugLevelComp(std::shared_ptr<dae::GameObject>& gameObject, unsigned gridWidth, unsigned gridHeight, const std::string& binFile);
	~DigDugLevelComp() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

private:
	void SpawnRock(std::shared_ptr<dae::GameObject>& rock);
	void DetermineWhenFalling(std::shared_ptr<dae::GameObject>& rock);
	int DetermineGridCell(const std::shared_ptr<dae::GameObject>& character, Direction direction);
	unsigned DetermineEmptyGrids(const Cell& start);

	std::shared_ptr<dae::Texture2D> m_TunnelTexture;
	std::vector<std::shared_ptr<TextureRenderComponent>> m_pTunnels;

	std::shared_ptr<dae::GameObject> m_pRock1;
	std::shared_ptr<dae::GameObject> m_pRock2;
	std::shared_ptr<dae::GameObject> m_pRock3;

	std::shared_ptr<dae::GameObject>& m_GameObject;
};

