#include "MiniginPCH.h"
#include "LevelComponent.h"
#include "CharacterComponent.h"
#include "BinaryReader.h"


LevelComponent::LevelComponent(std::string path,unsigned int gridWidth, unsigned int gridHeight, std::string file)
	: m_GridWidth(gridWidth)
	, m_GridHeight(gridHeight)
{
	m_Texture = std::make_shared<TextureRenderComponent>(path);
	BinaryReader levelFile{ file };
	const unsigned int width{ m_Texture->GetWidth() / gridWidth }, height{ m_Texture->GetHeight() / gridHeight };
	for (unsigned int i= 0; i < height; ++i)
	{
		for (unsigned int j = 0; j < width; ++j)
		{
			Cell grid{};
			grid.posX = j * m_GridWidth;
			grid.posY = i * m_GridHeight;
			grid.canWalkOn = true;
			grid.hasBeenVisited = false;
			if (i < 1 || i == height-1)
				grid.canWalkOn = false;
			if (i == 1)
				grid.hasBeenVisited = true;
			if (levelFile.Read<bool>())
			{
				std::shared_ptr<TextureRenderComponent> temp = std::make_shared<TextureRenderComponent>("Tunnel.png");
				temp->SetTransform(float(grid.posX), float(grid.posY), 1.0f);
				m_pTunnels.push_back(temp);
				grid.hasBeenVisited = true;
			}
			m_LevelGrid.push_back(grid);
		}
	}
	levelFile.CloseFile();
}

void LevelComponent::Update()
{

}

void LevelComponent::FixedUpdate()
{
	for (auto element : m_CharactersInLevel)
	{
		auto component = element->GetComponent<CharacterComponent>();
		if (component == nullptr)
			continue;
		if (!component->GetIsPlayer())
			continue;
		const int Current = DetermineGridCell(element, component->GetCurrentDirection());
		if (m_prevIdx == -1)
			m_prevIdx = Current;
		if (Current == -1)
			return;
		if (m_prevIdx != Current)
		{
			if (!m_LevelGrid[m_prevIdx].hasBeenVisited && !component->GetIsMovingAutomatic())
			{
				std::shared_ptr<TextureRenderComponent> temp = std::make_shared<TextureRenderComponent>("Tunnel.png");
				temp->SetTransform(float(m_LevelGrid[m_prevIdx].posX), float(m_LevelGrid[m_prevIdx].posY), 1.0f);
				m_pTunnels.push_back(temp);
				m_LevelGrid[m_prevIdx].hasBeenVisited = true;
			}
			m_prevIdx = Current;
		}
		if (!m_LevelGrid[Current].hasBeenVisited)
			component->SetIsPlayerDigging(true);
		else
			component->SetIsPlayerDigging(false);
	}
}

void LevelComponent::Render()
{
	m_Texture->Render();
	for (auto element : m_pTunnels)
		element->Render();
}

void LevelComponent::SetTransform(float x, float y, float z)
{
	m_Texture->SetTransform(x, y, z);
}

void LevelComponent::AddCharacterInScene(std::shared_ptr<dae::GameObject>& character)
{
	m_CharactersInLevel.push_back(character);
}

int LevelComponent::DetermineGridCell(const std::shared_ptr<dae::GameObject>& character, Direction direction)
{
	auto x = character->GetTransform()->GetPosition().x;
	auto y = character->GetTransform()->GetPosition().y;
	if (direction == down)
		y += m_GridHeight-1;
	else if (direction == right)
		x += m_GridWidth-1;

	for (unsigned int i = 0; i != m_LevelGrid.size(); ++i)
	{
		if (m_LevelGrid[i].posX <= x && m_LevelGrid[i].posX + m_GridWidth > x)
			if (m_LevelGrid[i].posY <= y && m_LevelGrid[i].posY + m_GridWidth > y)
				return i;
	}
	return -1;
}
