#pragma once
#include "BaseComponent.h"
#include "TextureRenderComponent.h"
#include "GameObject.h"
#include "CharacterComponent.h"

struct Cell
{
	unsigned idx;
	int posX, posY;
	bool canWalkOn;
	bool hasBeenVisited;
	bool HasStone = false;
};

class LevelComponent final : public BaseComponent
{
public:
	LevelComponent(std::string path, unsigned int gridWidth, unsigned int gridHeight, std::string file);
	virtual ~LevelComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

	void AddCharacterInScene(std::shared_ptr<dae::GameObject>& character);

private:
	void SpawnRock(std::shared_ptr<dae::GameObject>& rock);
	void DetermineWhenFalling(std::shared_ptr<dae::GameObject>& rock);
	int DetermineGridCell(const std::shared_ptr<dae::GameObject>& character, Direction direction);
	unsigned DetermineEmptyGrids(const Cell& start);

	std::shared_ptr<dae::Texture2D> m_TunnelTexture; 

	std::shared_ptr<TextureRenderComponent> m_Texture;
	float m_X = 0, m_Y = 0;
	unsigned int m_GridWidth = 0, m_GridHeight = 0;
	std::vector<Cell> m_LevelGrid;
	std::vector<std::shared_ptr<dae::GameObject>> m_CharactersInLevel;
	std::vector<std::shared_ptr<TextureRenderComponent>> m_pTunnels;
	
	std::shared_ptr<dae::GameObject> m_pRock1;
	std::shared_ptr<dae::GameObject> m_pRock2;
	std::shared_ptr<dae::GameObject> m_pRock3;

};

