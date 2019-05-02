#include "pch.h"
#include "StartScreen.h"
#include "GameObject.h"
#include "TextureRenderComponent.h"
#include "ButtonComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "FPSComponent.h"
#include "SoundManager.h"
#include "Command.h"


StartScreen::StartScreen()
	:GameScene("StartScreen")
{
}

void StartScreen::Initialize()
{
	std::shared_ptr<dae::GameObject> background = std::make_shared<dae::GameObject>();
	std::shared_ptr<TextureRenderComponent> texture = std::make_shared<TextureRenderComponent>("start_screen.png");
	background->AddComponent(texture);
	AddChild(background);

	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Up, InputTriggerState::Pressed, VK_UP, XINPUT_GAMEPAD_DPAD_UP), std::make_shared<ButtonUpCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Down, InputTriggerState::Pressed, VK_DOWN, XINPUT_GAMEPAD_DPAD_DOWN), std::make_shared<ButtonDownCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Select, InputTriggerState::Pressed, VK_SPACE, XINPUT_GAMEPAD_A), std::make_shared<ButtonSelectCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Quit, InputTriggerState::Pressed, VK_ESCAPE, XINPUT_GAMEPAD_X), std::make_shared<QuitCommand>());

	auto font = dae::ResourceManager::GetInstance().LoadFont("digdug.ttf", 32);
	m_ButtonManager = std::make_shared<ButtonManager>();

	std::shared_ptr<dae::GameObject> button = std::make_shared<dae::GameObject>();
	std::shared_ptr<ButtonComponent> buttonComp = std::make_shared<ButtonComponent>("Single", font, SDL_Color{ 0,0,0,255 }, 
		[]() {dae::SceneManager::GetInstance().SetActive("SingleLevel"); });
	button->AddComponent(buttonComp);
	button->SetPosition(250, 230, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	button = std::make_shared<dae::GameObject>();
	buttonComp = std::make_shared<ButtonComponent>("Co-op", font, SDL_Color{ 0,0,0,255 }, 
		[]() {dae::SceneManager::GetInstance().SetActive("CoopLevel"); });
	button->AddComponent(buttonComp);
	button->SetPosition(250, 280, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	button = std::make_shared<dae::GameObject>();
	buttonComp = std::make_shared<ButtonComponent>("Versus", font, SDL_Color{ 0,0,0,255 }, 
		[]() {dae::SceneManager::GetInstance().SetActive("VersusLevel"); });
	button->AddComponent(buttonComp);
	button->SetPosition(250, 330, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	button = std::make_shared<dae::GameObject>();
	buttonComp = std::make_shared<ButtonComponent>("Options", font, SDL_Color{ 0,0,0,255 }, 
		[]() {dae::SceneManager::GetInstance().SetActive("OptionsScreen"); });
	button->AddComponent(buttonComp);
	button->SetPosition(65, 480, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	button = std::make_shared<dae::GameObject>();
	buttonComp = std::make_shared<ButtonComponent>("Credits", font, SDL_Color{ 0,0,0,255 }, 
		[]() {dae::SceneManager::GetInstance().SetActive("CreditScreen"); });
	button->AddComponent(buttonComp);
	button->SetPosition(65, 530, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	m_ButtonManager->SetStartButtonByIdx(0);

	ServiceLocator::RegisterButtonManager(m_ButtonManager);

	//SoundManager::GetInstance().LoadSoundStream("Theme", "DigDugThemeSong.ogg");
	//SoundManager::GetInstance().PlaySoundStream("Theme", true);
}

void StartScreen::Update()
{
}

void StartScreen::FixedUpdate()
{
}

void StartScreen::Render() const
{
}