#include "pch.h"
#include "OptionsScreen.h"
#include "TextureRenderComponent.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SceneManager.h"
#include "Command.h"


OptionsScreen::OptionsScreen()
	:GameScene("OptionsScreen")
{
}

void OptionsScreen::Initialize()
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
	std::shared_ptr<ButtonComponent> buttonComp = std::make_shared<ButtonComponent>("Back", font, SDL_Color{ 0,0,0,255 }, []() {dae::SceneManager::GetInstance().SetActive("StartScreen"); });
	button->AddComponent(buttonComp);
	button->SetPosition(250, 230, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	m_ButtonManager->SetStartButtonByIdx(0);

	ServiceLocator::RegisterButtonManager(m_ButtonManager);
}

void OptionsScreen::Update()
{
}

void OptionsScreen::FixedUpdate()
{
}

void OptionsScreen::Render() const
{
}




