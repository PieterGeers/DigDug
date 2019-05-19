#include "MiniginPCH.h"
#include "LevelComponent.h"
#include "CharacterComponent.h"
#include "Node.h"
#include "AStarPathFinding.h"

std::vector<std::shared_ptr<Cell>> LevelComponent::m_LevelGrid;

LevelComponent::LevelComponent(unsigned texWidth, unsigned texHeight, unsigned gridWidth, unsigned gridHeight)
	: m_GridWidth(gridWidth)
	, m_GridHeight(gridHeight)
	, m_nbOfRows(texHeight / gridHeight)
	, m_nbOfColumns(texWidth / gridWidth)
{
	for (unsigned int i= 0; i < m_nbOfRows; ++i)
	{
		for (unsigned int j = 0; j < m_nbOfColumns; ++j)
		{
			std::shared_ptr<Cell> grid = std::make_shared<Cell>();
			grid->idx = i * m_nbOfColumns + j;
			grid->position = MVector2_INT( j * m_GridWidth,i * m_GridHeight);
			grid->canWalkOn = true;
			m_LevelGrid.push_back(grid);
		}
	}
}

void LevelComponent::Update()
{}

void LevelComponent::FixedUpdate()
{}

void LevelComponent::Render()
{}

void LevelComponent::SetTransform(float, float, float)
{}

void LevelComponent::CreateGraph(bool useDiagonal)
{
	if (!m_IsGraphMade)
	{
		auto& graph = AStarPathFinding::GetGraph();
		for (const auto cell : m_LevelGrid)
		{
			std::shared_ptr<Node> tmp = std::make_shared<Node>(cell->position);
			tmp->SetWalkable(true);
			graph.push_back(tmp);
		}
		for (unsigned i = 0; i != graph.size(); ++i)
		{
			//up
			if (int(i) - static_cast<int>(m_nbOfColumns) >= 0)
				graph[i]->AddConnection(graph[i - m_nbOfColumns].get());
			//down
			if (i + m_nbOfColumns < graph.size())
				graph[i]->AddConnection(graph[i + m_nbOfColumns].get());
			//left
			if ((i - 1) >= 0 && (i - 1) / m_nbOfColumns == i / m_nbOfColumns)
				graph[i]->AddConnection(graph[i - 1].get());
			//right
			if ((i + 1) < graph.size() && (i + 1) / m_nbOfColumns == i / m_nbOfColumns)
				graph[i]->AddConnection(graph[i + 1].get());
			if (useDiagonal)
			{
				//leftup
				if (int(i) - static_cast<int>(m_nbOfColumns) - 1 >= 0 &&
					(i - m_nbOfColumns - 1) / m_nbOfColumns == i / m_nbOfColumns - 1)
					graph[i]->AddConnection(graph[i - m_nbOfColumns - 1].get());
				//rightup
				if (int(i) - static_cast<int>(m_nbOfColumns) + 1 >= 0 &&
					(i - m_nbOfColumns + 1) / m_nbOfColumns == i / m_nbOfColumns - 1)
					graph[i]->AddConnection(graph[i - m_nbOfColumns + 1].get());
				//leftdown
				if (int(i) + static_cast<int>(m_nbOfColumns) - 1 >= 0 &&
					(i + m_nbOfColumns - 1) / m_nbOfColumns == i / m_nbOfColumns + 1)
					graph[i]->AddConnection(graph[i + m_nbOfColumns - 1].get());
				//rightdown
				if (int(i) + static_cast<int>(m_nbOfColumns) + 1 >= 0 &&
					(i + m_nbOfColumns + 1) / m_nbOfColumns == i / m_nbOfColumns + 1)
					graph[i]->AddConnection(graph[i + m_nbOfColumns + 1].get());
			}
		}
		m_IsGraphMade = true;
	}
}