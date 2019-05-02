#include "MiniginPCH.h"
#include "LevelComponent.h"

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

void LevelComponent::AddCharacterInScene(std::shared_ptr<dae::GameObject>& character)
{
	m_CharactersInLevel.push_back(character);
}

void LevelComponent::AddAgentInScene(std::shared_ptr<dae::GameObject>& agent)
{
	m_Agents.push_back(agent);
}

void LevelComponent::CreateGraph(bool useDiagonal)
{
	if (!m_IsGraphMade)
	{
		for (const auto cell : m_LevelGrid)
		{
			std::shared_ptr<Node> tmp = std::make_shared<Node>(cell->position);
			tmp->SetWalkable(true);
			m_Graph.push_back(tmp);
		}
		for (unsigned i = 0; i != m_Graph.size(); ++i)
		{
			//up
			if (int(i) - static_cast<int>(m_nbOfColumns) >= 0)
				m_Graph[i]->AddConnection(m_Graph[i - m_nbOfColumns]);
			//down
			if (i + m_nbOfColumns < m_Graph.size())
				m_Graph[i]->AddConnection(m_Graph[i + m_nbOfColumns]);
			//left
			if ((i - 1) >= 0 && (i - 1) / m_nbOfColumns == i / m_nbOfColumns)
				m_Graph[i]->AddConnection(m_Graph[i - 1]);
			//right
			if ((i + 1) < m_Graph.size() && (i + 1) / m_nbOfColumns == i / m_nbOfColumns)
				m_Graph[i]->AddConnection(m_Graph[i + 1]);
			if (useDiagonal)
			{
				//leftup
				//rightup
				//leftdown
				//rightdown
			}
		}
		m_IsGraphMade = true;
	}
}
