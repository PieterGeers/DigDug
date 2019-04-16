#include "MiniginPCH.h"
#include "Level.h"
#include "GameObject.h"
#include "LevelComponent.h"
#include "FPSComponent.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"


Level::Level()
	: GameScene("Level")
{
}

void Level::Initialize()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto& p1Input = ServiceLocator::GetInputP1();

	const std::shared_ptr<Command> moveUp = std::make_shared<MoveUpCommand>();
	const std::shared_ptr<Command> moveDown = std::make_shared<MoveDownCommand>();
	const std::shared_ptr<Command> moveLeft = std::make_shared<MoveLeftCommand>();
	const std::shared_ptr<Command> moveRight = std::make_shared<MoveRightCommand>();

	p1Input.SetButton(ControllerButton::Up, moveUp);
	p1Input.SetButton(ControllerButton::Down, moveDown);
	p1Input.SetButton(ControllerButton::Left, moveLeft);
	p1Input.SetButton(ControllerButton::Right, moveRight);

	m_DigDug = std::make_shared<dae::GameObject>();
	
	auto go = std::make_shared<dae::GameObject>();
	std::shared_ptr<LevelComponent> go_textures = std::make_shared<LevelComponent>("Level.png", 32, 32, "../Data/Levels/Level1.bin");
	go_textures->AddCharacterInScene(m_DigDug);
	go->AddComponent(go_textures);
	AddChild(go);

	std::shared_ptr<TextureRenderComponent> go_texture = std::make_shared<TextureRenderComponent>("digdug_spriteP1.png", 7, 7, 2);
	go_texture->SetSpritePosition(0, 0, 6, 6);
	std::shared_ptr<CharacterComponent> character = std::make_shared<CharacterComponent>(m_DigDug, Boundaries{32, 32*17,0,32*13});
	character->SetGridSize(32);
	m_DigDug->AddComponent(go_texture);
	m_DigDug->AddComponent(character);
	m_DigDug->SetPosition(0, 32, 0);
	AddChild(m_DigDug);

	auto fpsCounter = std::make_shared<dae::GameObject>();
	std::shared_ptr<FPSComponent> fps_component = std::make_shared<FPSComponent>(fpsFont, SDL_Color{ 255,255,0,255 });
	fpsCounter->AddComponent(fps_component);
	AddChild(fpsCounter);
}

void Level::Update()
{
	auto& p1Input = ServiceLocator::GetInputP1();
	if (p1Input.IsPressed(ControllerButton::Up))
		p1Input.GetCommand(ControllerButton::Up)->Execute(m_DigDug);
	else if (p1Input.IsPressed(ControllerButton::Down))
		p1Input.GetCommand(ControllerButton::Down)->Execute(m_DigDug);
	else if (p1Input.IsPressed(ControllerButton::Left))
		p1Input.GetCommand(ControllerButton::Left)->Execute(m_DigDug);
	else if (p1Input.IsPressed(ControllerButton::Right))
		p1Input.GetCommand(ControllerButton::Right)->Execute(m_DigDug);
}

void Level::FixedUpdate()
{
}

void Level::Render() const
{
}
