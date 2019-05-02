#include "pch.h"
#include "CoopLevel.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "FPSComponent.h"
#include "GameCommands.h"
#include "DigDugLevelComp.h"
#include "Structs.h"
#include "WeaponComponent.h"

CoopLevel::CoopLevel()
	: GameScene("CoopLevel")
{
}

void CoopLevel::Initialize()
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

	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Quit, InputTriggerState::Pressed, VK_ESCAPE, XINPUT_GAMEPAD_X), std::make_shared<QuitCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::up, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerOne),
		std::make_shared<MoveUpCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::down, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerOne),
		std::make_shared<MoveDownCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::left, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerOne),
		std::make_shared<MoveLeftCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::right, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerOne),
		std::make_shared<MoveRightCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::up, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerTwo),
		std::make_shared<MoveUpCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::down, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerTwo),
		std::make_shared<MoveDownCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::left, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerTwo),
		std::make_shared<MoveLeftCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(Direction::right, InputTriggerState::Down, -1, XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerTwo),
		std::make_shared<MoveRightCommand>());

	m_DigDugP1 = std::make_shared<dae::GameObject>();
	m_DigDugP2 = std::make_shared<dae::GameObject>();

	auto level = std::make_shared<dae::GameObject>();
	const std::shared_ptr<TextureRenderComponent> levelText = std::make_shared<TextureRenderComponent>("Level.png");
	level->AddComponent(levelText);
	std::shared_ptr<DigDugLevelComp> levelComp = std::make_shared<DigDugLevelComp>(level, 32, 32, "../Data/Levels/Level1.bin");
	levelComp->AddCharacterInScene(m_DigDugP1);
	levelComp->AddCharacterInScene(m_DigDugP2);
	level->AddComponent(levelComp);
	AddChild(level);

	std::shared_ptr<TextureRenderComponent> playerText = std::make_shared<TextureRenderComponent>("digdug_spriteP1.png", 7, 7, 2);
	playerText->SetSpritePosition(0, 0, 6, 6);
	std::shared_ptr<DigDugCharacterComp> character = std::make_shared<DigDugCharacterComp>(m_DigDugP1, Boundaries{ 32, 32 * 17,0,32 * 13 });
	character->AddAnimation(std::vector<std::shared_ptr<Animation>>{left, leftDig, right, rightDig, leftUp, rightUp, leftUpDig, rightUpDig, rightDown, leftDown, rightDownDig, leftDownDig});
	std::shared_ptr<WeaponComponent> weaponComp = std::make_shared<WeaponComponent>(m_DigDugP1, "digdug_attack.png", 1, 4, 2, true);
	character->SetGridSize(32);
	m_DigDugP1->AddComponent(playerText);
	m_DigDugP1->AddComponent(character);
	m_DigDugP1->AddComponent(weaponComp);
	m_DigDugP1->SetPosition(0, 32, 0);
	AddChild(m_DigDugP1);

	playerText = std::make_shared<TextureRenderComponent>("digdug_spriteP2.png", 7, 7, 2);
	playerText->SetSpritePosition(0, 0, 6, 6);
	character = std::make_shared<DigDugCharacterComp>(m_DigDugP2, Boundaries{ 32, 32 * 17,0,32 * 13 });
	character->AddAnimation(std::vector<std::shared_ptr<Animation>>{left, leftDig, right, rightDig, leftUp, rightUp, leftUpDig, rightUpDig, rightDown, leftDown, rightDownDig, leftDownDig});
	weaponComp = std::make_shared<WeaponComponent>(m_DigDugP2, "digdug_attack.png", 1, 4, 2, true);
	character->SetGridSize(32);
	m_DigDugP2->AddComponent(playerText);
	m_DigDugP2->AddComponent(character);
	m_DigDugP2->AddComponent(weaponComp);
	m_DigDugP2->SetPosition(416, 32, 0);
	AddChild(m_DigDugP2);

	auto fpsCounter = std::make_shared<dae::GameObject>();
	std::shared_ptr<FPSComponent> fps_component = std::make_shared<FPSComponent>(fpsFont, SDL_Color{ 255,255,0,255 });
	fpsCounter->AddComponent(fps_component);
	AddChild(fpsCounter);

}

void CoopLevel::Update()
{}

void CoopLevel::FixedUpdate()
{}

void CoopLevel::Render() const
{}