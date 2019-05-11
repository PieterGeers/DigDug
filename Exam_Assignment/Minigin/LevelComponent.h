#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "Structs.h"

class Node;
class LevelComponent : public BaseComponent
{
public:
	LevelComponent(unsigned texWidth, unsigned texHeight, unsigned gridWidth, unsigned gridHeight);
	~LevelComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float x, float y, float z) override;

	void CreateGraph(bool useDiagonal = false);
	static std::vector<std::shared_ptr<Cell>>& GetGrid() { return m_LevelGrid; }

protected:
	unsigned m_nbOfRows = 0, m_nbOfColumns = 0;
	unsigned m_GridWidth = 0, m_GridHeight = 0;
	static std::vector<std::shared_ptr<Cell>> m_LevelGrid;

private:
	bool m_IsGraphMade = false;
};

