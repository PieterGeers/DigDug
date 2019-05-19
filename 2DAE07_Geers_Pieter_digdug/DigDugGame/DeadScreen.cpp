#include "pch.h"
#include "DeadScreen.h"
#include "GameObject.h"
#include "TextureRenderComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SceneManager.h"
#include "Command.h"
#include "SoundManager.h"

DeadScreen::DeadScreen()
	:GameScene("DeadScreen")
{
}

void DeadScreen::Initialize()
{
	if (!SoundManager::GetInstance().IsSoundStreamPlaying("UISound"))
		SoundManager::GetInstance().PlaySoundStream("UISound", true);

	std::shared_ptr<GameObject> background = std::make_shared<GameObject>();
	std::shared_ptr<TextureRenderComponent> texture = std::make_shared<TextureRenderComponent>("start_screen.png");
	background->AddComponent(texture);
	AddChild(background);

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