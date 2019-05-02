#include "pch.h"
#include "DigDugLevelComp.h"
#include "BinaryReader.h"
#include "ResourceManager.h"
#include "CharacterComponent.h"
#include "RockComponent.h"
#include "DigDugStructs.h"
#include "DigDugCharacterComp.h"
#include "GameTime.h"
#include "TransformComponent.h"

DigDugLevelComp::DigDugLevelComp(unsigned levelWidth, unsigned levelHeight, unsigned gridWidth, unsigned gridHeight, const std::string& binFile)
	:LevelComponent(levelWidth, levelHeight, gridWidth, gridHeight)
{
	m_TunnelTexture = dae::ResourceManager::GetInstance().LoadTexture("Tunnel.png");
	BinaryReader levelFile{ binFile };
	for (unsigned i = 0; i != m_LevelGrid.size(); ++i)
	{
		std::shared_ptr<DigDugCell> temp = std::make_shared<DigDugCell>();
		temp->idx = m_LevelGrid[i]->idx;
		temp->position = m_LevelGrid[i]->position;
		temp->canWalkOn = m_LevelGrid[i]->canWalkOn;
		temp->hasVisited = false;
		if (temp->idx < m_nbOfColumns || temp->idx >= m_nbOfColumns * (m_nbOfRows - 1))
			temp->canWalkOn = false;
		if (temp->idx >= m_nbOfColumns && temp->idx < m_nbOfColumns * 2)
			temp->hasVisited = true;
		if (levelFile.Read<bool>())
		{
			std::shared_ptr<TextureRenderComponent> tempTex = std::make_shared<TextureRenderComponent>(m_TunnelTexture);
			tempTex->SetTransform(float(temp->position.x), float(temp->position.y), 1.0f);
			m_pTunnels.push_back(tempTex);
			temp->hasVisited = true;
		}
		m_LevelGrid[i] = temp;
	}
	levelFile.CloseFile();

	SpawnRock(m_pRock1);
	SpawnRock(m_pRock2);
	SpawnRock(m_pRock3);
	
}

void DigDugLevelComp::Update()
{
	m_pRock1->Update();
	m_pRock2->Update();
	m_pRock3->Update();
}

void DigDugLevelComp::Render()
{
	for (auto element : m_pTunnels)
		element->Render();
	m_pRock1->Render();
	m_pRock2->Render();
	m_pRock3->Render();
}

void DigDugLevelComp::SetTransform(float, float, float)
{
}

void DigDugLevelComp::FixedUpdate()
{
	for (auto element : m_CharactersInLevel)
	{
		auto component = element->GetComponent<DigDugCharacterComp>();
		if (component == nullptr)
			continue;
		const int Current = DetermineGridCell(element, component->GetCurrentDirection());
		if (component->GetPreviousLocation() == -1)
			component->SetPreviousLocation(Current);
		const int prevIdx = component->GetPreviousLocation();
		if (Current == -1)
			return;
		if (prevIdx != Current)
		{
			if (!std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[prevIdx])->hasVisited && !component->GetIsMovingAutomatic())
			{
				std::shared_ptr<TextureRenderComponent> temp = std::make_shared<TextureRenderComponent>(m_TunnelTexture);
				temp->SetTransform(float(std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[prevIdx])->position.x), float(std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[prevIdx])->position.y), 1.0f);
				m_pTunnels.push_back(temp);
				std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[prevIdx])->hasVisited = true;
			}
			component->SetPreviousLocation(Current);
		}
		if (!std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[Current])->hasVisited)
			component->SetIsPlayerDigging(true);
		else
			component->SetIsPlayerDigging(false);
	}

	DetermineWhenFalling(m_pRock1);
	DetermineWhenFalling(m_pRock2);
	DetermineWhenFalling(m_pRock3);

	m_pRock1->FixedUpdate();
	m_pRock2->FixedUpdate();
	m_pRock3->FixedUpdate();

}

void DigDugLevelComp::SpawnRock(std::shared_ptr<GameObject>& rock)
{
	const unsigned totalCells = m_nbOfColumns * m_nbOfRows;

	unsigned rockIdx = rand() % totalCells;
	while (rockIdx < m_nbOfColumns * 2 || rockIdx > totalCells - 2 * m_nbOfColumns || std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx])->hasVisited || std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx + m_nbOfColumns])->hasVisited || std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx])->hasStone)
	{
		rockIdx = rand() % totalCells;
	}
	std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx])->hasStone = true;
	rock = std::make_shared<GameObject>();
	const std::shared_ptr<RockComponent> comp = std::make_shared<RockComponent>(*std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx + m_nbOfColumns]), "rock.png");
	rock->AddComponent(comp);
	rock->SetPosition(float(std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx])->position.x), float(std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx])->position.y), 0.0f);
}

void DigDugLevelComp::DetermineWhenFalling(std::shared_ptr<GameObject>& rock)
{
	auto component = rock->GetComponent<RockComponent>();
	if (component == nullptr)
		return;
	if (component->IsRockActive() == false)
		return;
	if (component->GetCell().hasVisited == true && !component->IsFalling())
	{
		//check if a player is under the rock
		for (auto element : m_CharactersInLevel)
		{
			auto CharComponent = element->GetComponent<DigDugCharacterComp>();
			if (CharComponent == nullptr)
				continue;
			const int width = component->GetTexture()->GetWidth() - 1;
			if (((int(element->GetTransform()->GetPosition().x) <= component->GetCell().position.x + width &&
				int(element->GetTransform()->GetPosition().x) >= component->GetCell().position.x) ||
				(int(element->GetTransform()->GetPosition().x) + width <= component->GetCell().position.x + width &&
					int(element->GetTransform()->GetPosition().x) + width >= component->GetCell().position.x)) && element->GetTransform()->GetPosition().y >= component->GetCell().position.y)
				return;
		}
		//check how many empty spaces are under the rock
		component->FallForAmountCell(DetermineEmptyGrids(component->GetCell()));
	}
}

int DigDugLevelComp::DetermineGridCell(const std::shared_ptr<GameObject>& character, Direction direction)
{
	auto x = character->GetTransform()->GetPosition().x;
	auto y = character->GetTransform()->GetPosition().y;
	if (direction == down)
		y += m_GridHeight - 1;
	else if (direction == right)
		x += m_GridWidth - 1;

	for (unsigned int i = 0; i != m_LevelGrid.size(); ++i)
	{
		if (std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[i])->position.x <= x && std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[i])->position.x + m_GridWidth > x)
			if (std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[i])->position.y <= y && std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[i])->position.y + m_GridWidth > y)
				return i;
	}
	return -1;
}

unsigned DigDugLevelComp::DetermineEmptyGrids(const Cell& start)
{
	unsigned nbOfGrids{ 0 };
	for (unsigned i = start.idx; i <= m_LevelGrid.size() - m_nbOfColumns; i += m_nbOfColumns)
	{
		if (std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[i])->hasVisited)
			++nbOfGrids;
		else
			return nbOfGrids;
	}
	return nbOfGrids;
}