#include "pch.h"
#include "DigDugLevelComp.h"
#include "BinaryReader.h"
#include "ResourceManager.h"
#include "CharacterComponent.h"
#include "DigDugStructs.h"
#include "DigDugCharacterComp.h"
#include "GameTime.h"
#include "TransformComponent.h"
#include "QuadCollisionComponent.h"
#include "DigDugRockComp.h"
#include "ServiceLocator.h"
#include "algorithm"
#include "FygarCharacterComp.h"
#include "DigDugLivesComp.h"

DigDugLevelComp::DigDugLevelComp(unsigned levelWidth, unsigned levelHeight, unsigned gridWidth, unsigned gridHeight, unsigned nbOfRocks, const std::string& binFile)
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
			m_EnemySpawnPositions.push_back({ temp->position });
		}
		m_LevelGrid[i] = temp;
	}
	levelFile.CloseFile();
	SpawnRock(nbOfRocks);
	CreateGraph();
}

void DigDugLevelComp::Update()
{
	for (auto rock = m_Rocks.begin(); rock != m_Rocks.end(); ++rock)
	{
		(*rock)->Update();
		if (!(*rock)->GetComponent<DigDugRockComp>()->IsRockActive())
		{
			std::string tag = (*rock)->GetComponent<QuadCollisionComponent>()->GetTag();
			auto it = QuadCollisionComponent::GetCollisionObjects().find(tag);
			QuadCollisionComponent::GetCollisionObjects().erase(it);
			m_Rocks.erase(std::remove(m_Rocks.begin(), m_Rocks.end(), (*rock)), m_Rocks.end());
			if (m_Rocks.size() > 0)
				rock = m_Rocks.begin();
			else
				return;
		}
	}
}

void DigDugLevelComp::Render()
{
	for (auto element : m_pTunnels)
		element->Render();
	for (const auto rock : m_Rocks)
		rock->Render();
}

void DigDugLevelComp::SetTransform(float, float, float)
{
}

std::vector<MVector2_INT> DigDugLevelComp::GetSpawnPosition(int nbOfSpawnPosition)
{
	if (nbOfSpawnPosition > static_cast<int>(m_EnemySpawnPositions.size()))
		Debug::LogError("NbOfEnemies exceeds nb of free spawn spaces");
	std::vector<MVector2_INT> availablePositions;
	for (int i = 0; i < nbOfSpawnPosition; ++i)
	{
		int idx = rand() % static_cast<int>(m_EnemySpawnPositions.size());
		auto temp = m_EnemySpawnPositions[idx];
		availablePositions.push_back(temp);
		m_EnemySpawnPositions[idx] = m_EnemySpawnPositions[m_EnemySpawnPositions.size() - 1];
		m_EnemySpawnPositions[m_EnemySpawnPositions.size() - 1] = temp;
		m_EnemySpawnPositions.pop_back();
	}
	return availablePositions;
}

void DigDugLevelComp::FixedUpdate()
{
	for (auto element : ServiceLocator::GetPlayers())
	{
		bool isPlayer = true;
		auto component = element.second->GetComponent<DigDugCharacterComp>();
		auto component2 = element.second->GetComponent<FygarCharacterComp>();
		if (component == nullptr)
			isPlayer = false;
		if (component == nullptr && component2 == nullptr)
				continue;
		const int Current = DetermineGridCell(element.second, (isPlayer) ? component->GetCurrentDirection() : component2->GetCurrentDirection());
		if (isPlayer && component->GetPreviousLocation() == -1)
			component->SetPreviousLocation(Current);
		else if (!isPlayer && component2->GetPreviousLocation() == -1)
			component2->SetPreviousLocation(Current);
		const int prevIdx = (isPlayer) ? component->GetPreviousLocation() : component2->GetPreviousLocation();
		if (Current == -1)
			return;
		if (prevIdx != Current && isPlayer)
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
		{
			if (isPlayer)
				component->SetIsPlayerDigging(true);
			else
				component2->SetIsPlayerInvisible(true);
		}
		else
		{
			if (isPlayer)
				component->SetIsPlayerDigging(false);
			else
				component2->SetIsPlayerInvisible(false);
		}
	}
	for (auto element : ServiceLocator::GetPlayers())
	{
		auto coll = element.second->GetComponent<QuadCollisionComponent>();
		for (auto rock : m_Rocks)
		{
			if (rock->GetComponent<DigDugRockComp>()->IsFalling())
			{
				std::string tag = rock->GetComponent<QuadCollisionComponent>()->GetTag();
				if (coll->CheckIfCollisionWith(tag, static_cast<unsigned>(tag.size())))
				{
					element.second->GetComponent<DigDugLivesComp>()->HealthLost();
				}
			}
		}
	}
	for (auto rock : m_Rocks)
		DetermineWhenFalling(rock);

	for (auto rock : m_Rocks)
		rock->FixedUpdate();
}

void DigDugLevelComp::SpawnRock(unsigned amount)
{
	const unsigned totalCells = m_nbOfColumns * m_nbOfRows;
	for (unsigned i = 0; i < amount; ++i)
	{
		unsigned rockIdx = rand() % totalCells;
		while (rockIdx < m_nbOfColumns * 2 || rockIdx > totalCells - 2 * m_nbOfColumns || std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx])->hasVisited || std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx + m_nbOfColumns])->hasVisited || std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx])->hasStone)
		{
			rockIdx = rand() % totalCells;
		}
		std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx])->hasStone = true;
		std::shared_ptr<GameObject> rock = std::make_shared<GameObject>();
		const std::shared_ptr<DigDugRockComp> comp = std::make_shared<DigDugRockComp>(*std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx + m_nbOfColumns]), "rock.png");
		const std::shared_ptr<QuadCollisionComponent> collision = std::make_shared<QuadCollisionComponent>(MVector2_INT(0, 0), 32, "Rock" + std::to_string(rockIdx));
		rock->AddComponent(comp);
		rock->AddComponent(collision);
		rock->SetPosition(float(std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx])->position.x), float(std::reinterpret_pointer_cast<DigDugCell>(m_LevelGrid[rockIdx])->position.y), 0.0f);
		m_Rocks.push_back(rock);
	}
}

void DigDugLevelComp::DetermineWhenFalling(std::shared_ptr<GameObject>& rock)
{
	auto component = rock->GetComponent<DigDugRockComp>();
	if (component == nullptr)
		return;
	if (component->IsRockActive() == false)
		return;
	if (component->GetCell().hasVisited == true && !component->IsFalling())
	{
		//check if a player is under the rock
		for (auto element : ServiceLocator::GetPlayers())
		{
			auto CharComponent = element.second->GetComponent<DigDugCharacterComp>();
			if (CharComponent == nullptr)
				continue;
			const int width = component->GetTexture()->GetWidth() - 1;
			if (((int(element.second->GetTransform()->GetPosition().x) <= component->GetCell().position.x + width &&
				int(element.second->GetTransform()->GetPosition().x) >= component->GetCell().position.x) ||
				(int(element.second->GetTransform()->GetPosition().x) + width <= component->GetCell().position.x + width &&
					int(element.second->GetTransform()->GetPosition().x) + width >= component->GetCell().position.x)) && element.second->GetTransform()->GetPosition().y >= component->GetCell().position.y)
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