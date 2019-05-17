#include "pch.h"
#include "DeadScreen.h"
#include "GameObject.h"
#include "TextureRenderComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SceneManager.h"
#include "Command.h"

DeadScreen::DeadScreen()
	:GameScene("DeadScreen")
{
}

void DeadScreen::Initialize()
{
	std::shared_ptr<GameObject> background = std::make_shared<GameObject>();
	std::shared_ptr<TextureRenderComponent> texture = std::make_shared<TextureRenderComponent>("start_screen.png");
	background->AddComponent(texture);
	AddChild(background);

//	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Up, InputTriggerState::Pressed, VK_UP, XINPUT_GAMEPAD_DPAD_UP), std::make_shared<ButtonUpCommand>());
//	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Down, InputTriggerState::Pressed, VK_DOWN, XINPUT_GAMEPAD_DPAD_DOWN), std::make_shared<ButtonDownCommand>());
//	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Select, InputTriggerState::Pressed, VK_SPACE, XINPUT_GAMEPAD_A), std::make_shared<ButtonSelectCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Quit, InputTriggerState::Pressed, VK_ESCAPE, XINPUT_GAMEPAD_X), std::make_shared<QuitCommand>());

	auto font = dae::ResourceManager::GetInstance().LoadFont("digdug.ttf", 32);
	auto score = dae::ResourceManager::GetInstance().LoadFont("PressStart2P.ttf", 24);

	std::shared_ptr<GameObject> text = std::make_shared<GameObject>();
	std::shared_ptr<TextRenderComponent> t1 = std::make_shared<TextRenderComponent>("You Died ...", font, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> t2 = std::make_shared<TextRenderComponent>("Again", font, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> t3 = std::make_shared<TextRenderComponent>("Score ", font, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> t4 = std::make_shared<TextRenderComponent>(std::to_string(m_Score), score, SDL_Color{ 0,0,0,255 });
	t1->SetTransform(220, 260, 0);
	t2->SetTransform(240, 300, 0);
	t3->SetTransform(50, 470, 0);
	t4->SetTransform(100, 510, 0);
	text->AddComponent(t1);
	text->AddComponent(t2);
	text->AddComponent(t3);
	text->AddComponent(t4);
	AddChild(text);

	//m_ButtonManager = std::make_shared<ButtonManager>();

	/*std::shared_ptr<GameObject> button = std::make_shared<GameObject>();
	std::shared_ptr<ButtonComponent> buttonComp = std::make_shared<ButtonComponent>("Main Menu", font, SDL_Color{ 0,0,0,255 }, []() {dae::SceneManager::GetInstance().SetActive("StartScreen"); });
	button->AddComponent(buttonComp);
	button->SetPosition(200, 220, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	m_ButtonManager->SetStartButtonByIdx(0);

	ServiceLocator::RegisterButtonManager(m_ButtonManager);*/

}

void DeadScreen::Update()
{
}

void DeadScreen::FixedUpdate()
{
}

void DeadScreen::Render() const
{
}