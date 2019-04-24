#include "MiniginPCH.h"
#include "LevelComponent.h"
#include "CharacterComponent.h"
#include "BinaryReader.h"
#include "RockComponent.h"
#include "ResourceManager.h"

//static const std::shared_ptr<dae::Texture2D> m_TunnelTexture;

LevelComponent::LevelComponent(std::string path,unsigned int gridWidth, unsigned int gridHeight, std::string file)
	: m_GridWidth(gridWidth)
	, m_GridHeight(gridHeight)
{
	m_TunnelTexture = dae::ResourceManager::GetInstance().LoadTexture("Tunnel.png");
	m_Texture = std::make_shared<TextureRenderComponent>(path);
	BinaryReader levelFile{ file };
	const unsigned int width{ m_Texture->GetWidth() / gridWidth }, height{ m_Texture->GetHeight() / gridHeight };
	for (unsigned int i= 0; i < height; ++i)
	{
		for (unsigned int j = 0; j < width; ++j)
		{
			Cell grid{};
			grid.idx = i * width + j;
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
				std::shared_ptr<TextureRenderComponent> temp = std::make_shared<TextureRenderComponent>(m_TunnelTexture);
				temp->SetTransform(float(grid.posX), float(grid.posY), 1.0f);
				m_pTunnels.push_back(temp);
				grid.hasBeenVisited = true;
			}
			m_LevelGrid.push_back(grid);
		}
	}
	levelFile.CloseFile();
	//spawn rocks
	SpawnRock(m_pRock1);
	SpawnRock(m_pRock2);
	SpawnRock(m_pRock3);
}

void LevelComponent::Update()
{
	m_pRock1->Update();
	m_pRock2->Update();
	m_pRock3->Update();
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
		if (component->GetPreviousLocation() == -1)
			component->SetPreviousLocation(Current);
		const int prevIdx = component->GetPreviousLocation();
		if (Current == -1)
			return;
		if (prevIdx != Current)
		{
			if (!m_LevelGrid[prevIdx].hasBeenVisited && !component->GetIsMovingAutomatic())
			{
				std::shared_ptr<TextureRenderComponent> temp = std::make_shared<TextureRenderComponent>(m_TunnelTexture);
				temp->SetTransform(float(m_LevelGrid[prevIdx].posX), float(m_LevelGrid[prevIdx].posY), 1.0f);
				m_pTunnels.push_back(temp);
				m_LevelGrid[prevIdx].hasBeenVisited = true;
			}
			component->SetPreviousLocation(Current);
		}
		if (!m_LevelGrid[Current].hasBeenVisited)
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

void LevelComponent::Render()
{
	m_Texture->Render();
	for (auto element : m_pTunnels)
		element->Render();
	m_pRock1->Render();
	m_pRock2->Render();
	m_pRock3->Render();
}

void LevelComponent::SetTransform(float x, float y, float z)
{
	m_Texture->SetTransform(x, y, z);
}

void LevelComponent::AddCharacterInScene(std::shared_ptr<dae::GameObject>& character)
{
	m_CharactersInLevel.push_back(character);
}

void LevelComponent::SpawnRock(std::shared_ptr<dae::GameObject>& rock)
{
	const unsigned int width{ m_Texture->GetWidth() / m_GridWidth }, height{ m_Texture->GetHeight() / m_GridHeight };
	const unsigned totalCells = width * height;

	unsigned rockIdx = rand() % totalCells;
	while (rockIdx < width * 2 || rockIdx > totalCells - 2 * width || m_LevelGrid[rockIdx].hasBeenVisited || m_LevelGrid[rockIdx + width].hasBeenVisited || m_LevelGrid[rockIdx].HasStone)
	{
		rockIdx = rand() % totalCells;
	}
	m_LevelGrid[rockIdx].HasStone = true;
	rock = std::make_shared<dae::GameObject>();
	const std::shared_ptr<RockComponent> comp = std::make_shared<RockComponent>(rock, m_LevelGrid[rockIdx + width], "rock.png");
	rock->AddComponent(comp);
	rock->SetPosition(float(m_LevelGrid[rockIdx].posX), float(m_LevelGrid[rockIdx].posY), 0.0f);
}

void LevelComponent::DetermineWhenFalling(std::shared_ptr<dae::GameObject>& rock)
{
	auto component = rock->GetComponent<RockComponent>();
	if (component == nullptr)
		return;
	if (component->IsRockActive() == false)
		return;
	if (component->GetCell().hasBeenVisited == true && !component->IsFalling())
	{
		//check if a player is under the rock
		for (auto element : m_CharactersInLevel)
		{
			auto CharComponent = element->GetComponent<CharacterComponent>();
			if (CharComponent == nullptr)
				continue;
			if (CharComponent->GetIsPlayer() == false)
				continue;
			const int width = component->GetTexture()->GetWidth() - 1;
			if (((int(element->GetTransform()->GetPosition().x) <= component->GetCell().posX + width &&
				int(element->GetTransform()->GetPosition().x) >= component->GetCell().posX) || 
				(int(element->GetTransform()->GetPosition().x) + width <= component->GetCell().posX + width &&
				int(element->GetTransform()->GetPosition().x) + width >= component->GetCell().posX)) && element->GetTransform()->GetPosition().y >= component->GetCell().posY)
				return;
		}
		//check how many empty spaces are under the rock
		component->FallForAmountCell(DetermineEmptyGrids(component->GetCell()));
	}
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

unsigned LevelComponent::DetermineEmptyGrids(const Cell& start)
{
	const unsigned width = m_Texture->GetWidth() / m_GridWidth;
	unsigned nbOfGrids{ 0 };
	for (unsigned i = start.idx; i <= m_LevelGrid.size() - width; i+=width)
	{
		if (m_LevelGrid[i].hasBeenVisited)
			++nbOfGrids;
		else
			return nbOfGrids;
	}
	return nbOfGrids;
}
