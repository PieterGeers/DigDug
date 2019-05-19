#include "pch.h"
#include "DigDugGame.h"
#include "SceneManager.h"
#include "StartScreen.h"
#include "CoopLevel.h"
#include "VersusLevel.h"
#include "OptionsScreen.h"
#include "CreditScreen.h"
#include "ServiceLocator.h"
#include "SingleLevel.h"
#include "GameTime.h"
#include "InputManager.h"
#include <chrono>
#include "DeadScreen.h"
#include "SoundManager.h"

DigDugGame::DigDugGame(){}
DigDugGame::~DigDugGame(){}

void DigDugGame::LoadGame() const
{
	//set fixed time in GameTime
	dae::GameTime::GetInstance().SetFixedElapsed(std::chrono::duration<float>(std::chrono::milliseconds(GetMs())).count());
	InputManager::GetInstance().Initialize();
	ServiceLocator::Init();

	SoundManager::GetInstance().LoadSoundStream("UISound", "DigDugUISound.ogg");
	SoundManager::GetInstance().LoadSoundStream("GameSong", "DigDugBackGround.ogg");
	SoundManager::GetInstance().LoadSoundEffect("Loss", "DigDugLoss.ogg");
	SoundManager::GetInstance().LoadSoundEffect("DDAttack", "DigDugAttack.ogg");
	SoundManager::GetInstance().LoadSoundEffect("Victory", "DigDugVictory.ogg");
	SoundManager::GetInstance().LoadSoundEffect("EAttack", "DigDugEnemyAttack.ogg");

	//Set game scenes here
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<StartScreen>());
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<SingleLevel>());
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<CoopLevel>());
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<VersusLevel>());
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<OptionsScreen>());
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<CreditScreen>());
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<DeadScreen>());
	dae::SceneManager::GetInstance().SetActive("StartScreen");
}
