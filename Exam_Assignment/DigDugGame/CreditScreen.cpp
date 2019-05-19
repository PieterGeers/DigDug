#include "pch.h"
#include "CreditScreen.h"
#include "TextureRenderComponent.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Command.h"
#include "SoundManager.h"


CreditScreen::CreditScreen()
	:GameScene("CreditScreen")
{
}

void CreditScreen::Initialize()
{
	if (!SoundManager::GetInstance().IsSoundStreamPlaying("UISound"))
		SoundManager::GetInstance().PlaySoundStream("UISound", true);

	std::shared_ptr<GameObject> background = std::make_shared<GameObject>();
	std::shared_ptr<TextureRenderComponent> texture = std::make_shared<TextureRenderComponent>("credit_screen.png");
	background->AddComponent(texture);
	AddChild(background);

	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Up, InputTriggerState::Pressed, 'W', XINPUT_GAMEPAD_DPAD_UP), std::make_shared<ButtonUpCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Down, InputTriggerState::Pressed, 'S', XINPUT_GAMEPAD_DPAD_DOWN), std::make_shared<ButtonDownCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Select, InputTriggerState::Pressed, VK_SPACE, XINPUT_GAMEPAD_A), std::make_shared<ButtonSelectCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Quit, InputTriggerState::Pressed, VK_ESCAPE, XINPUT_GAMEPAD_X), std::make_shared<QuitCommand>());

	auto font = dae::ResourceManager::GetInstance().LoadFont("digdug.ttf", 32);
	auto credits = dae::ResourceManager::GetInstance().LoadFont("digdug.ttf", 24);

	m_ButtonManager = std::make_shared<ButtonManager>();

	std::shared_ptr<GameObject> button = std::make_shared<GameObject>();
	std::shared_ptr<ButtonComponent> buttonComp = std::make_shared<ButtonComponent>("Back", font, SDL_Color{ 0,0,0,255 }, []() {dae::SceneManager::GetInstance().SetActive("StartScreen"); });
	button->AddComponent(buttonComp);
	button->SetPosition(250, 180, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	m_ButtonManager->SetStartButtonByIdx(0);

	ServiceLocator::RegisterButtonManager(m_ButtonManager);

	std::shared_ptr<GameObject> credit = std::make_shared<GameObject>();
	std::shared_ptr<TextRenderComponent> art0 = std::make_shared<TextRenderComponent>("Made by Pieter Geers", credits, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> art = std::make_shared<TextRenderComponent>("UI Art by The-Driz", credits, SDL_Color{0,0,0,255});
	std::shared_ptr<TextRenderComponent> art_1 = std::make_shared<TextRenderComponent>("and RingoStarr39", credits, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> art1 = std::make_shared<TextRenderComponent>("Sound by GameNoises", credits, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> art2 = std::make_shared<TextRenderComponent>("Sprites by Black Squirrel", credits, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> art3 = std::make_shared<TextRenderComponent>("and Superjustinbros", credits, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> art3_5 = std::make_shared<TextRenderComponent>("Font by SpideRaYsfoNtS", credits, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> art3_75 = std::make_shared<TextRenderComponent>("and Cody Boisclair", credits, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> art4 = std::make_shared<TextRenderComponent>("Inspired by Elite", credits, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> art5 = std::make_shared<TextRenderComponent>("and Overlord engine", credits, SDL_Color{ 0,0,0,255 });
	art0->SetTransform(100, 240, 0);
	art->SetTransform(100, 275, 0);
	art_1->SetTransform(150, 310, 0);
	art1->SetTransform(100, 345, 0);
	art2->SetTransform(100, 380, 0);
	art3->SetTransform(150, 415, 0);
	art3_5->SetTransform(100, 450, 0);
	art3_75->SetTransform(150, 485, 0);
	art4->SetTransform(100, 520, 0);
	art5->SetTransform(150, 555, 0);
	credit->AddComponent(art0);
	credit->AddComponent(art);
	credit->AddComponent(art_1);
	credit->AddComponent(art1);
	credit->AddComponent(art2);
	credit->AddComponent(art3);
	credit->AddComponent(art3_5);
	credit->AddComponent(art3_75);
	credit->AddComponent(art4);
	credit->AddComponent(art5);
	AddChild(credit);
}

void CreditScreen::Update()
{
}

void CreditScreen::FixedUpdate()
{

}

void CreditScreen::Render() const
{
}
