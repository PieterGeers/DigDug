#include "pch.h"
#include "SingleLevel.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "GameCommands.h"
#include "DigDugLevelComp.h"
#include "InputManager.h"
#include "Animator.h"
#include "ResourceManager.h"
#include "QuadCollisionComponent.h"
#include "EntitySpawn.h"
#include "DigDugStructs.h"
#include "DigDugLivesComp.h"
#include "SceneManager.h"
#include "DeadScreen.h"
#include "AgentComponent.h"
#include "Score.h"
#include "SoundManager.h"

SingleLevel::SingleLevel()
	: GameScene("SingleLevel")
{
}

void SingleLevel::Initialize()
{
	if (!SoundManager::GetInstance().IsSoundStreamPlaying("GameSong"))
		SoundManager::GetInstance().PlaySoundStream("GameSong", true);

	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	InputManager::GetInstance().AddInputAction(InputAction(P1Up, InputTriggerState::Down, 'W', XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerOne),
		std::make_shared<MoveUpCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P1Down, InputTriggerState::Down, 'S', XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerOne),
		std::make_shared<MoveDownCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P1Left, InputTriggerState::Down, 'A', XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerOne),
		std::make_shared<MoveLeftCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P1Right, InputTriggerState::Down, 'D', XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerOne),
		std::make_shared<MoveRightCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Quit, InputTriggerState::Pressed, VK_ESCAPE, XINPUT_GAMEPAD_X), std::make_shared<QuitCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P1Attack, InputTriggerState::Pressed, VK_SPACE, XINPUT_GAMEPAD_A, GamepadIndex::PlayerOne),
		std::make_shared<DigDugAttackCommand>());

	std::shared_ptr<GameObject> LevelObject = std::make_shared<GameObject>();
	const std::shared_ptr<TextureRenderComponent> levelTexture = std::make_shared<TextureRenderComponent>("Level.png");
	std::shared_ptr<DigDugLevelComp> levelComp = std::make_shared<DigDugLevelComp>(levelTexture->GetWidth(), levelTexture->GetHeight(), 32, 32, 3, "../Data/Levels/Level1.bin");
	LevelObject->AddComponent(levelTexture);
	LevelObject->AddComponent(levelComp);
	AddChild(LevelObject);
	levelComp->CreateGraph();

	auto fpsCounter = std::make_shared<GameObject>();
	std::shared_ptr<FPSComponent> fps_component = std::make_shared<FPSComponent>(fpsFont, SDL_Color{ 255,255,0,255 });
	fpsCounter->AddComponent(fps_component);
	AddChild(fpsCounter);

	auto SpawnPositions = levelComp->GetSpawnPosition(4);
	//PLAYER
	//******
	AddChild(EntitySpawn::SpawnPlayer({ 0,32 }, "digdug_spriteP0.png", static_cast<int>(PlayerOne) ));
	//POOKA
	//*****
	AddChild(EntitySpawn::SpawnPooka(SpawnPositions[0], "Enemy1"));
	AddChild(EntitySpawn::SpawnPooka(SpawnPositions[1], "Enemy2"));
	//FYGAR
	//*****
	AddChild(EntitySpawn::SpawnFygar(SpawnPositions[2], "Enemy3"));
	AddChild(EntitySpawn::SpawnFygar(SpawnPositions[3], "Enemy4"));

	Score::GetInstance().Initialize();
}

void SingleLevel::Update()
{
	bool GameOver = true;
	for (auto player : ServiceLocator::GetPlayers())
	{
		if (player.second->GetComponent<DigDugLivesComp>()->GetNumberOfLives() > 0)
		{
			GameOver = false;
		}
	}
	if (!GameOver && ServiceLocator::GetAgents().size() == 0)
	{
		//load next level
		if (m_CurrentLevel == 2)
			m_CurrentLevel = 1;
		else
			++m_CurrentLevel;
		SoundManager::GetInstance().PlaySoundEffect("Victory", 0);
		QuadCollisionComponent::GetCollisionObjects().clear();
		ServiceLocator::GetAgents().clear();
		ServiceLocator::GetPlayers().clear();
		ResetScene();
	}
	else if (GameOver)
	{
		//load end screen
		QuadCollisionComponent::GetCollisionObjects().clear();
		for (auto element : ServiceLocator::GetAgents())
		{
			auto comp = element.second->GetComponent<AgentComponent>();
			element.second->RemoveComponent(comp);
		}
		ServiceLocator::GetAgents().clear();
		ServiceLocator::GetPlayers().clear();
		AgentComponent::ResetCount();
		ClearGameObjects();
		std::static_pointer_cast<DeadScreen>(dae::SceneManager::GetInstance().GetGameScene("DeadScreen"))->SetScore(Score::GetInstance().GetScore());
		dae::SceneManager::GetInstance().SetActive("DeadScreen");
	}
}

void SingleLevel::FixedUpdate()
{
	QuadCollisionComponent::HandleQuadCollision();
}

void SingleLevel::Render() const
{
	Score::GetInstance().Render();
}

void SingleLevel::ResetScene()
{
	ClearGameObjects();
	ReloadScene();
}

void SingleLevel::ReloadScene()
{
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	std::shared_ptr<GameObject> LevelObject = std::make_shared<GameObject>();
	const std::shared_ptr<TextureRenderComponent> levelTexture = std::make_shared<TextureRenderComponent>("Level.png");
	std::shared_ptr<DigDugLevelComp> levelComp = std::make_shared<DigDugLevelComp>(levelTexture->GetWidth(), levelTexture->GetHeight(), 32, 32, 3, "../Data/Levels/Level" + std::to_string(m_CurrentLevel) + ".bin");
	LevelObject->AddComponent(levelTexture);
	LevelObject->AddComponent(levelComp);
	AddChild(LevelObject);
	levelComp->CreateGraph();

	auto fpsCounter = std::make_shared<GameObject>();
	std::shared_ptr<FPSComponent> fps_component = std::make_shared<FPSComponent>(fpsFont, SDL_Color{ 255,255,0,255 });
	fpsCounter->AddComponent(fps_component);
	AddChild(fpsCounter);

	auto SpawnPositions = levelComp->GetSpawnPosition(4);
	//PLAYER
	//******
	AddChild(EntitySpawn::SpawnPlayer({ 0,32 }, "digdug_spriteP0.png", static_cast<int>(PlayerOne)));
	//POOKA
	//*****
	AddChild(EntitySpawn::SpawnPooka(SpawnPositions[0], "Enemy1"));
	AddChild(EntitySpawn::SpawnPooka(SpawnPositions[1], "Enemy2"));
	//FYGAR
	//*****
	AddChild(EntitySpawn::SpawnFygar(SpawnPositions[2], "Enemy3"));
	AddChild(EntitySpawn::SpawnFygar(SpawnPositions[3], "Enemy4"));
}
