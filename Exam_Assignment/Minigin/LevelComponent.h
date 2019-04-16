#pragma once
#include "BaseComponent.h"
#include "TextureRenderComponent.h"
#include "GameObject.h"
#include "CharacterComponent.h"


class LevelComponent final : public BaseComponent
{
	struct Cell
	{
		int posX, posY;
		bool canWalkOn;
		bool hasBeenVisited;
	};

public:
	LevelComponent(std::string path, unsigned int gridWidth, unsigned int gridHeight, std::string file);
	virtual ~LevelComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

	void AddCharacterInScene(std::shared_ptr<dae::GameObject>& character);

private:
	int DetermineGridCell(const std::shared_ptr<dae::GameObject>& character, Direction direction);

	std::shared_ptr<TextureRenderComponent> m_Texture;
	float m_X = 0, m_Y = 0;
	unsigned int m_GridWidth = 0, m_GridHeight = 0;
	std::vector<Cell> m_LevelGrid;
	std::vector<std::shared_ptr<dae::GameObject>> m_CharactersInLevel;
	int m_prevIdx = -1;
	std::vector<std::shared_ptr<TextureRenderComponent>> m_pTunnels;
};

