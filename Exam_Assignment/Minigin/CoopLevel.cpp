#include "MiniginPCH.h"
#include "CoopLevel.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "LevelComponent.h"
#include "FPSComponent.h"


CoopLevel::CoopLevel()
	: GameScene("CoopLevel")
{
}

void CoopLevel::Initialize()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	std::shared_ptr<Input> service = std::make_shared<PlayerInput>();
	ServiceLocator::RegisterInputP2Service(service);

	auto& p1Input = ServiceLocator::GetInputP1();
	auto& p2Input = ServiceLocator::GetInputP2();

	const std::shared_ptr<Command> moveUp = std::make_shared<MoveUpCommand>();
	const std::shared_ptr<Command> moveDown = std::make_shared<MoveDownCommand>();
	const std::shared_ptr<Command> moveLeft = std::make_shared<MoveLeftCommand>();
	const std::shared_ptr<Command> moveRight = std::make_shared<MoveRightCommand>();

	p1Input->SetButton(ControllerButton::Up, moveUp);
	p1Input->SetButton(ControllerButton::Down, moveDown);
	p1Input->SetButton(ControllerButton::Left, moveLeft);
	p1Input->SetButton(ControllerButton::Right, moveRight);

	p2Input->SetButton(ControllerButton::Up, moveUp);
	p2Input->SetButton(ControllerButton::Down, moveDown);
	p2Input->SetButton(ControllerButton::Left, moveLeft);
	p2Input->SetButton(ControllerButton::Right, moveRight);

	m_DigDugP1 = std::make_shared<dae::GameObject>();
	m_DigDugP2 = std::make_shared<dae::GameObject>();

	auto level = std::make_shared<dae::GameObject>();
	std::shared_ptr<LevelComponent> levelComp = std::make_shared<LevelComponent>("Level.png", 32, 32, "../Data/Levels/Level1.bin");
	levelComp->AddCharacterInScene(m_DigDugP1);
	levelComp->AddCharacterInScene(m_DigDugP2);
	level->AddComponent(levelComp);
	AddChild(level);

	std::shared_ptr<TextureRenderComponent> playerText = std::make_shared<TextureRenderComponent>("digdug_spriteP1.png", 7, 7, 2);
	playerText->SetSpritePosition(0, 0, 6, 6);
	std::shared_ptr<CharacterComponent> character = std::make_shared<CharacterComponent>(m_DigDugP1, Boundaries{ 32, 32 * 17,0,32 * 13 });
	character->SetGridSize(32);
	m_DigDugP1->AddComponent(playerText);
	m_DigDugP1->AddComponent(character);
	m_DigDugP1->SetPosition(0, 32, 0);
	AddChild(m_DigDugP1);

	playerText = std::make_shared<TextureRenderComponent>("digdug_spriteP2.png", 7, 7, 2);
	playerText->SetSpritePosition(0, 0, 6, 6);
	character = std::make_shared<CharacterComponent>(m_DigDugP2, Boundaries{ 32, 32 * 17,0,32 * 13 });
	character->SetGridSize(32);
	m_DigDugP2->AddComponent(playerText);
	m_DigDugP2->AddComponent(character);
	m_DigDugP2->SetPosition(416, 32, 0);
	AddChild(m_DigDugP2);

	auto fpsCounter = std::make_shared<dae::GameObject>();
	std::shared_ptr<FPSComponent> fps_component = std::make_shared<FPSComponent>(fpsFont, SDL_Color{ 255,255,0,255 });
	fpsCounter->AddComponent(fps_component);
	AddChild(fpsCounter);
}

void CoopLevel::Update()
{
	auto& p1Input = ServiceLocator::GetInputP1();
	auto& p2Input = ServiceLocator::GetInputP2();
	if (p1Input->IsPressed(ControllerButton::Up))
		p1Input->GetCommand(ControllerButton::Up)->Execute(m_DigDugP1);
	else if (p1Input->IsPressed(ControllerButton::Down))
		p1Input->GetCommand(ControllerButton::Down)->Execute(m_DigDugP1);
	else if (p1Input->IsPressed(ControllerButton::Left))
		p1Input->GetCommand(ControllerButton::Left)->Execute(m_DigDugP1);
	else if (p1Input->IsPressed(ControllerButton::Right))
		p1Input->GetCommand(ControllerButton::Right)->Execute(m_DigDugP1);
	if (p2Input->IsPressed(ControllerButton::Up))
		p2Input->GetCommand(ControllerButton::Up)->Execute(m_DigDugP2);
	else if (p2Input->IsPressed(ControllerButton::Down))
		p2Input->GetCommand(ControllerButton::Down)->Execute(m_DigDugP2);
	else if (p2Input->IsPressed(ControllerButton::Left))
		p2Input->GetCommand(ControllerButton::Left)->Execute(m_DigDugP2);
	else if (p2Input->IsPressed(ControllerButton::Right))
		p2Input->GetCommand(ControllerButton::Right)->Execute(m_DigDugP2);
}

void CoopLevel::FixedUpdate()
{
}

void CoopLevel::Render() const
{
}
