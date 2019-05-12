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
#include "AgentComponent.h"
#include "EntitySpawn.h"


SingleLevel::SingleLevel()
	: GameScene("SingleLevel")
{
}

void SingleLevel::Initialize()
{
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	InputManager::GetInstance().AddInputAction(InputAction(Direction::up, InputTriggerState::Down, 'W', XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerOne),
		std::make_shared<MoveUpCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::down, InputTriggerState::Down, 'S', XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerOne),
		std::make_shared<MoveDownCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::left, InputTriggerState::Down, 'A', XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerOne),
		std::make_shared<MoveLeftCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::right, InputTriggerState::Down, 'D', XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerOne),
		std::make_shared<MoveRightCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Quit, InputTriggerState::Pressed, VK_ESCAPE, XINPUT_GAMEPAD_X), std::make_shared<QuitCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(4, InputTriggerState::Pressed, 'Q', XINPUT_GAMEPAD_A, GamepadIndex::PlayerOne),
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
}

void SingleLevel::Update()
{

}

void SingleLevel::FixedUpdate()
{
	QuadCollisionComponent::HandleQuadCollision();
}

void SingleLevel::Render() const
{
}
