#include "pch.h"
#include "CoopLevel.h"
#include "ResourceManager.h"
#include "FPSComponent.h"
#include "GameCommands.h"
#include "DigDugLevelComp.h"
#include "Structs.h"
#include "Animator.h"
#include "EntitySpawn.h"
#include "DigDugStructs.h"
#include "QuadCollisionComponent.h"
#include "DigDugLivesComp.h"
#include "DeadScreen.h"
#include "SceneManager.h"
#include "Score.h"

CoopLevel::CoopLevel()
	: GameScene("CoopLevel")
{
}

void CoopLevel::Initialize()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	InputManager::GetInstance().AddInputAction(InputAction(P1Up, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerOne),
		std::make_shared<MoveUpCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P1Down, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerOne),
		std::make_shared<MoveDownCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P1Left, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerOne),
		std::make_shared<MoveLeftCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P1Right, InputTriggerState::Down,-1, XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerOne),
		std::make_shared<MoveRightCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Quit, InputTriggerState::Pressed, VK_ESCAPE, XINPUT_GAMEPAD_X), std::make_shared<QuitCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P1Attack, InputTriggerState::Pressed, -1, XINPUT_GAMEPAD_A, GamepadIndex::PlayerOne),
		std::make_shared<DigDugAttackCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P2Up, InputTriggerState::Down, 'W', XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerTwo),
		std::make_shared<MoveUpCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P2Down, InputTriggerState::Down, 'S', XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerTwo),
		std::make_shared<MoveDownCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P2Left, InputTriggerState::Down, 'A', XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerTwo),
		std::make_shared<MoveLeftCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P2Right, InputTriggerState::Down, 'D', XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerTwo),
		std::make_shared<MoveRightCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(P2Attack, InputTriggerState::Pressed, 'Q', XINPUT_GAMEPAD_A, GamepadIndex::PlayerTwo),
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

	auto SpawnPositions = levelComp->GetSpawnPosition(6);
	//PLAYER
	//******
	AddChild(EntitySpawn::SpawnPlayer({ 0,32 }, "digdug_spriteP0.png", static_cast<int>(PlayerOne)));
	AddChild(EntitySpawn::SpawnPlayer({ 416, 32 }, "digdug_spriteP1.png", static_cast<int>(PlayerTwo), true, {416,576}));
	//POOKA
	//*****
	AddChild(EntitySpawn::SpawnPooka(SpawnPositions[0], "Enemy1"));
	AddChild(EntitySpawn::SpawnPooka(SpawnPositions[1], "Enemy2"));
	AddChild(EntitySpawn::SpawnPooka(SpawnPositions[2], "Enemy3"));
	//FYGAR
	//*****
	AddChild(EntitySpawn::SpawnFygar(SpawnPositions[3], "Enemy4"));
	AddChild(EntitySpawn::SpawnFygar(SpawnPositions[4], "Enemy5"));
	AddChild(EntitySpawn::SpawnFygar(SpawnPositions[5], "Enemy6"));

	Score::GetInstance().Initialize();
}

void CoopLevel::Update()
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
		QuadCollisionComponent::GetCollisionObjects().clear();
		ServiceLocator::GetAgents().clear();
		ServiceLocator::GetPlayers().clear();
		ResetScene();
	}
	else if (GameOver)
	{
		//load end screen
		//QuadCollisionComponent::GetCollisionObjects().clear();
		//ServiceLocator::GetAgents().clear();
		//ServiceLocator::GetPlayers().clear();
		//AgentComponent::ResetCount();
		std::static_pointer_cast<DeadScreen>(dae::SceneManager::GetInstance().GetGameScene("DeadScreen"))->SetScore(Score::GetInstance().GetScore());
		dae::SceneManager::GetInstance().SetActive("DeadScreen");
	}

}

void CoopLevel::FixedUpdate()
{
	QuadCollisionComponent::HandleQuadCollision();
}

void CoopLevel::Render() const
{
	Score::GetInstance().Render();
}

void CoopLevel::ResetScene()
{
	ClearGameObjects();
	ReloadScene();
}

void CoopLevel::ReloadScene()
{
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

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

	auto SpawnPositions = levelComp->GetSpawnPosition(6);
	//PLAYER
	//******
	AddChild(EntitySpawn::SpawnPlayer({ 0,32 }, "digdug_spriteP0.png", static_cast<int>(PlayerOne)));
	AddChild(EntitySpawn::SpawnPlayer({ 416, 32 }, "digdug_spriteP1.png", static_cast<int>(PlayerTwo), true, { 416,576 }));
	//POOKA
	//*****
	AddChild(EntitySpawn::SpawnPooka(SpawnPositions[0], "Enemy1"));
	AddChild(EntitySpawn::SpawnPooka(SpawnPositions[1], "Enemy2"));
	AddChild(EntitySpawn::SpawnPooka(SpawnPositions[2], "Enemy3"));
	//FYGAR
	//*****
	AddChild(EntitySpawn::SpawnFygar(SpawnPositions[3], "Enemy4"));
	AddChild(EntitySpawn::SpawnFygar(SpawnPositions[4], "Enemy5"));
	AddChild(EntitySpawn::SpawnFygar(SpawnPositions[5], "Enemy6"));

}
