#include "pch.h"
#include "SingleLevel.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "GameCommands.h"
#include "DigDugLevelComp.h"
#include "WeaponComponent.h"
#include "InputManager.h"


SingleLevel::SingleLevel()
	: GameScene("SingleLevel")
{
}

void SingleLevel::Initialize()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	const std::shared_ptr<Animation> left = CreateAnimation("Left", 1, 0, 0, 1);
	const std::shared_ptr<Animation> leftDig = CreateAnimation("LeftDig", 1, 2, 0, 1);
	const std::shared_ptr<Animation> right = CreateAnimation("Right", 0, 0, 0, 1);
	const std::shared_ptr<Animation> rightDig = CreateAnimation("RightDig", 0, 2, 0, 1);
	const std::shared_ptr<Animation> rightUp = CreateAnimation("RightUp", 5, 0, 0, 1);
	const std::shared_ptr<Animation> leftUp = CreateAnimation("LeftUp", 4, 0, 0, 1);
	const std::shared_ptr<Animation> rightUpDig = CreateAnimation("RightUpDig", 5, 2, 0, 1);
	const std::shared_ptr<Animation> leftUpDig = CreateAnimation("LeftUpDig", 4, 2, 0, 1);
	const std::shared_ptr<Animation> rightDown = CreateAnimation("RightDown", 2, 0, 0, 1);
	const std::shared_ptr<Animation> leftDown = CreateAnimation("LeftDown", 3, 0, 0, 1);
	const std::shared_ptr<Animation> rightDownDig = CreateAnimation("RightDownDig", 2, 2, 0, 1);
	const std::shared_ptr<Animation> leftDownDig = CreateAnimation("LeftDownDig", 3, 2, 0, 1);
	
	m_DigDug = std::make_shared<dae::GameObject>();

	InputManager::GetInstance().AddInputAction(InputAction(Direction::up, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerOne),
		std::make_shared<MoveUpCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::down, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerOne),
		std::make_shared<MoveDownCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::left, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerOne),
		std::make_shared<MoveLeftCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::right, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerOne),
		std::make_shared<MoveRightCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Quit, InputTriggerState::Pressed, VK_ESCAPE, XINPUT_GAMEPAD_X), std::make_shared<QuitCommand>());


	auto go = std::make_shared<dae::GameObject>();
	const std::shared_ptr<TextureRenderComponent> levelText = std::make_shared<TextureRenderComponent>("Level.png");
	go->AddComponent(levelText);
	std::shared_ptr<DigDugLevelComp> levelComp = std::make_shared<DigDugLevelComp>(go, 32, 32, "../Data/Levels/Level1.bin");
	levelComp->AddCharacterInScene(m_DigDug);
	go->AddComponent(levelComp);
	AddChild(go);

	std::shared_ptr<TextureRenderComponent> go_texture = std::make_shared<TextureRenderComponent>("digdug_spriteP1.png", 7, 7, 2);
	go_texture->SetSpritePosition(0, 0, 6, 6);
	std::shared_ptr<DigDugCharacterComp> character = std::make_shared<DigDugCharacterComp>(m_DigDug, Boundaries{ 32, 32 * 17,0,32 * 13 });
	character->AddAnimation(std::vector<std::shared_ptr<Animation>>{left, leftDig, right, rightDig, leftUp, rightUp, leftUpDig, rightUpDig, rightDown, leftDown, rightDownDig, leftDownDig});
	std::shared_ptr<WeaponComponent> weapon = std::make_shared<WeaponComponent>(m_DigDug, "digdug_attack.png", 1, 4, 2, true);
	character->SetGridSize(32);
	m_DigDug->AddComponent(go_texture);
	m_DigDug->AddComponent(character);
	m_DigDug->AddComponent(weapon);
	m_DigDug->SetPosition(0, 32, 0);
	AddChild(m_DigDug);

	auto fpsCounter = std::make_shared<dae::GameObject>();
	std::shared_ptr<FPSComponent> fps_component = std::make_shared<FPSComponent>(fpsFont, SDL_Color{ 255,255,0,255 });
	fpsCounter->AddComponent(fps_component);
	AddChild(fpsCounter);

	ServiceLocator::RegisterP1Service(m_DigDug);

}

void SingleLevel::Update()
{
}

void SingleLevel::FixedUpdate()
{
}

void SingleLevel::Render() const
{
}
