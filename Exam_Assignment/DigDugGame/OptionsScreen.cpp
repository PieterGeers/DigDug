#include "pch.h"
#include "OptionsScreen.h"
#include "TextureRenderComponent.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SceneManager.h"
#include "Command.h"
#include "SoundManager.h"

int OptionsScreen::m_CurrentEffectVolume = 5;
int OptionsScreen::m_CurrentStreamVolume = 3;
OptionsScreen::OptionsScreen()
	:GameScene("OptionsScreen")
{
}

void OptionsScreen::Initialize()
{
	if (!SoundManager::GetInstance().IsSoundStreamPlaying("UISound"))
		SoundManager::GetInstance().PlaySoundStream("UISound", true);


	std::shared_ptr<GameObject> background = std::make_shared<GameObject>();
	std::shared_ptr<TextureRenderComponent> texture = std::make_shared<TextureRenderComponent>("options_screen.png");
	std::shared_ptr<TextureRenderComponent> options = std::make_shared<TextureRenderComponent>("info.png");
	background->AddComponent(texture);
	background->AddComponent(options);
	AddChild(background);

	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Up, InputTriggerState::Pressed, 'W', XINPUT_GAMEPAD_DPAD_UP), std::make_shared<ButtonUpCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Down, InputTriggerState::Pressed, 'S', XINPUT_GAMEPAD_DPAD_DOWN), std::make_shared<ButtonDownCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Select, InputTriggerState::Pressed, VK_SPACE, XINPUT_GAMEPAD_A), std::make_shared<ButtonSelectCommand>());
	InputManager::GetInstance().AddInputAction(InputAction(BasicActions::B_Quit, InputTriggerState::Pressed, VK_ESCAPE, XINPUT_GAMEPAD_X), std::make_shared<QuitCommand>());

	auto font = dae::ResourceManager::GetInstance().LoadFont("digdug.ttf", 32);
	m_ButtonManager = std::make_shared<ButtonManager>();

	std::shared_ptr<GameObject> music = std::make_shared<GameObject>();
	std::shared_ptr<TextRenderComponent> musicText = std::make_shared<TextRenderComponent>("Music", font, SDL_Color{ 0,0,0,255 });
	std::shared_ptr<TextRenderComponent> effectText = std::make_shared<TextRenderComponent>("Effect", font, SDL_Color{ 0,0,0,255 });
	musicText->SetTransform(20, 220, 0);
	effectText->SetTransform(20, 260, 0);
	music->AddComponent(musicText);
	music->AddComponent(effectText);
	AddChild(music);


	std::shared_ptr<GameObject> button = std::make_shared<GameObject>();
	std::shared_ptr<ButtonComponent> buttonComp = std::make_shared<ButtonComponent>("Back", font, SDL_Color{ 0,0,0,255 }, []() {dae::SceneManager::GetInstance().SetActive("StartScreen"); });
	button->AddComponent(buttonComp);
	button->SetPosition(200, 180, 0);
	AddChild(button);
	m_ButtonManager->AddButton(button);

	std::shared_ptr<GameObject> ssMin = std::make_shared<GameObject>();
	std::shared_ptr<ButtonComponent> buttonStreamMin = std::make_shared<ButtonComponent>("-", font, SDL_Color{ 0,0,0,255 }, []()
	{
		SoundManager::GetInstance().AddSoundStreamVolume(-10);
		UpdateSoundStreamVolume(-1);
	});
	ssMin->AddComponent(buttonStreamMin);
	ssMin->SetPosition(125, 220, 0);
	AddChild(ssMin);
	m_ButtonManager->AddButton(ssMin);

	std::shared_ptr<GameObject> ssPlus = std::make_shared<GameObject>();
	std::shared_ptr<ButtonComponent> buttonStreamPlus = std::make_shared<ButtonComponent>("+", font, SDL_Color{ 0,0,0,255 }, []()
	{
		SoundManager::GetInstance().AddSoundStreamVolume(10);
		UpdateSoundStreamVolume(1);
	});
	ssPlus->AddComponent(buttonStreamPlus);
	ssPlus->SetPosition(400, 220, 0);
	AddChild(ssPlus);
	m_ButtonManager->AddButton(ssPlus);

	std::shared_ptr<GameObject> seMin = std::make_shared<GameObject>();
	std::shared_ptr<ButtonComponent> buttonEffectMin = std::make_shared<ButtonComponent>("-", font, SDL_Color{ 0,0,0,255 }, []()
	{
		SoundManager::GetInstance().AddSoundEffectVolume(-10);
		UpdateSoundEffectVolume(-1);
	});
	seMin->AddComponent(buttonEffectMin);
	seMin->SetPosition(125, 260, 0);
	AddChild(seMin);
	m_ButtonManager->AddButton(seMin);

	std::shared_ptr<GameObject> sePlus = std::make_shared<GameObject>();
	std::shared_ptr<ButtonComponent> buttonEffectPlus = std::make_shared<ButtonComponent>("+", font, SDL_Color{ 0,0,0,255 }, []()
	{
		SoundManager::GetInstance().AddSoundEffectVolume(10);
		UpdateSoundEffectVolume(1);
	});
	sePlus->AddComponent(buttonEffectPlus);
	sePlus->SetPosition(400, 260, 0);
	AddChild(sePlus);
	m_ButtonManager->AddButton(sePlus);

	for (int i = 0; i < 10; ++i)
	{
		std::shared_ptr<TextureRenderComponent> temp = std::make_shared<TextureRenderComponent>("audiobar.png");
		temp->SetTransform(static_cast<float>((400 - 25) - i * 25), 220, 0);
		m_StreamBars.push_back(temp);
	}
	for (int i = 0; i < 10; ++i)
	{
		std::shared_ptr<TextureRenderComponent> temp = std::make_shared<TextureRenderComponent>("audiobar.png");
		temp->SetTransform(static_cast<float>((400 - 25) - i * 25), 260, 0);
		m_EffectBars.push_back(temp);
	}
	std::reverse(m_StreamBars.begin(), m_StreamBars.end());
	std::reverse(m_EffectBars.begin(), m_EffectBars.end());

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
	for (int i = 0; i < m_CurrentStreamVolume; ++i)
	{
		m_StreamBars[i]->Render();
	}
	for (int i = 0; i < m_CurrentEffectVolume; ++i)
	{
		m_EffectBars[i]->Render();
	}

}

void OptionsScreen::UpdateSoundEffectVolume(int value)
{
	m_CurrentEffectVolume += value;
	if (m_CurrentEffectVolume < 0)
		m_CurrentEffectVolume = 0;
	if (m_CurrentEffectVolume > 10)
		m_CurrentEffectVolume = 10;
}

void OptionsScreen::UpdateSoundStreamVolume(int value)
{
	m_CurrentStreamVolume += value;
	if (m_CurrentStreamVolume < 0)
		m_CurrentStreamVolume = 0;
	if (m_CurrentStreamVolume > 10)
		m_CurrentStreamVolume = 10;
}