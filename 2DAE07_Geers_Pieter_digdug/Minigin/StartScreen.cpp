#include "MiniginPCH.h"
#include "StartScreen.h"
#include "GameObject.h"
#include "TextureRenderComponent.h"
#include "ButtonComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ServiceLocator.h"


StartScreen::StartScreen()
	:GameScene("StartScene")
{
}

void StartScreen::Initialize()
{
	std::shared_ptr<dae::GameObject> background = std::make_shared<dae::GameObject>();
	std::shared_ptr<TextureRenderComponent> texture = std::make_shared<TextureRenderComponent>("start_screen.png");
	background->AddComponent(texture);
	AddChild(background);

	auto font = dae::ResourceManager::GetInstance().LoadFont("digdug.ttf", 32);
	m_ButtonManager = std::make_shared<ButtonManager>();
	auto& p1Input = ServiceLocator::GetInputP1();

	const std::shared_ptr<Command> ButtonSelect = std::make_shared<ButtonSelectCommand>();

	p1Input->SetButton(ControllerButton::ButtonA, ButtonSelect);

	std::shared_ptr<dae::GameObject> button = std::make_shared<dae::GameObject>();
	std::shared_ptr<ButtonComponent> buttonComp = std::make_shared<ButtonComponent>("Single", font, SDL_Color{ 0,0,0,255 }, []() {dae::SceneManager::GetInstance().SetActive("Level"); });
	button->AddComponent(buttonComp);
	button->SetPosition(250, 230, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	button = std::make_shared<dae::GameObject>();
	buttonComp = std::make_shared<ButtonComponent>("Co-op", font, SDL_Color{ 0,0,0,255 }, []() {dae::SceneManager::GetInstance().SetActive("CoopLevel"); });
	button->AddComponent(buttonComp);
	button->SetPosition(250, 280, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	button = std::make_shared<dae::GameObject>();
	buttonComp = std::make_shared<ButtonComponent>("Versus", font, SDL_Color{ 0,0,0,255 }, []() { dae::SceneManager::GetInstance().SetActive("VersusLevel"); });
	button->AddComponent(buttonComp);
	button->SetPosition(250, 330, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	button = std::make_shared<dae::GameObject>();
	buttonComp = std::make_shared<ButtonComponent>("Options", font, SDL_Color{ 0,0,0,255 }, []() { });
	button->AddComponent(buttonComp);
	button->SetPosition(65, 480, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	button = std::make_shared<dae::GameObject>();
	buttonComp = std::make_shared<ButtonComponent>("Credits", font, SDL_Color{ 0,0,0,255 }, []() { });
	button->AddComponent(buttonComp);
	button->SetPosition(65, 530, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	m_ButtonManager->SetStartButtonByIdx(0);
}

void StartScreen::Update()
{
	m_ButtonManager->Update();
}

void StartScreen::FixedUpdate()
{
}

void StartScreen::Render() const
{
}


