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
#include "DigDugWeaponComp.h"
#include "DigDugLivesComp.h"


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

	m_DigDug = std::make_shared<GameObject>();

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
	std::shared_ptr<DigDugLevelComp> levelComp = std::make_shared<DigDugLevelComp>(levelTexture->GetWidth(), levelTexture->GetHeight(), 32, 32, "../Data/Levels/Level1.bin");
	LevelObject->AddComponent(levelTexture);
	LevelObject->AddComponent(levelComp);
	AddChild(LevelObject);

	std::shared_ptr<TextureRenderComponent> DigDugTexture = std::make_shared<TextureRenderComponent>("digdug_spriteP1.png", 7, 7, 2);
	std::shared_ptr<DigDugCharacterComp> character = std::make_shared<DigDugCharacterComp>(Boundaries{ 32, 32 * 17,0,32 * 13 });
	std::shared_ptr<Animator> animator = std::make_shared<Animator>();
	std::shared_ptr<QuadCollisionComponent> collision = std::make_shared<QuadCollisionComponent>(MVector2_INT(0, 0), 32, "Player1");
	std::shared_ptr<DigDugLivesComp> lives = std::make_shared<DigDugLivesComp>("P1Live.png", 3, MVector2_INT(0, 576));
	animator->AddAnimation(std::vector<std::shared_ptr<Animation>>{left, leftDig, right, rightDig, leftUp, rightUp, leftUpDig, rightUpDig, rightDown, leftDown, rightDownDig, leftDownDig});
	DigDugTexture->SetSpritePosition(0, 0, 6, 6);
	character->SetGridSize(32);
	m_DigDug->AddComponent(DigDugTexture);
	m_DigDug->AddComponent(character);
	m_DigDug->AddComponent(animator);
	m_DigDug->AddComponent(collision);
	m_DigDug->AddComponent(lives);

	std::shared_ptr<GameObject> Weapon = std::make_shared<GameObject>();
	std::shared_ptr<DigDugWeaponComp> weaponComp = std::make_shared<DigDugWeaponComp>("digdug_attack.png", 1, 4, 2);
	std::shared_ptr<Animator> weaponAnimator = std::make_shared<Animator>();
	std::shared_ptr<QuadCollisionComponent> weaponColl = std::make_shared<QuadCollisionComponent>(MVector2_INT(0, 0), 32, "Player1Attack");
	weaponColl->SetIsActive(false);
	const std::shared_ptr<Animation> aLeft = CreateAnimation("Left", 0, 3, 0, 0);
	const std::shared_ptr<Animation> aRight = CreateAnimation("Right", 0, 2, 0, 0);
	const std::shared_ptr<Animation> aUp = CreateAnimation("Up", 0, 0, 0, 0);
	const std::shared_ptr<Animation> aDown = CreateAnimation("Down", 0, 1, 0, 0);
	weaponAnimator->AddAnimation(std::vector<std::shared_ptr<Animation>>{aLeft, aRight, aUp, aDown});
	Weapon->AddComponent(weaponComp);
	Weapon->AddComponent(weaponAnimator);
	Weapon->AddComponent(weaponColl);

	m_DigDug->AddChild("Weapon", Weapon);
	m_DigDug->SetPosition(0, 32, 0);
	levelComp->AddCharacterInScene(m_DigDug);
	AddChild(m_DigDug);


	auto fpsCounter = std::make_shared<GameObject>();
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
	QuadCollisionComponent::HandleQuadCollision();
}

void SingleLevel::Render() const
{
}
