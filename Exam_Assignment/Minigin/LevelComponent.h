#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "Structs.h"
#include "Node.h"

class LevelComponent : public BaseComponent
{
public:
	LevelComponent(unsigned texWidth, unsigned texHeight, unsigned gridWidth, unsigned gridHeight);
	~LevelComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

	void AddCharacterInScene(std::shared_ptr<dae::GameObject>& character);
	void AddAgentInScene(std::shared_ptr<dae::GameObject>& agent);

	void CreateGraph(bool useDiagonal = false);

protected:
	unsigned m_nbOfRows = 0, m_nbOfColumns = 0;
	unsigned m_GridWidth = 0, m_GridHeight = 0;
	std::vector<std::shared_ptr<Cell>> m_LevelGrid;
	std::vector<std::shared_ptr<dae::GameObject>> m_CharactersInLevel;
	std::vector<std::shared_ptr<dae::GameObject>> m_Agents;
	std::vector<std::shared_ptr<Node>> m_Graph;

private:
	bool m_IsGraphMade = false;
};

