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

DigDugGame::DigDugGame(){}
DigDugGame::~DigDugGame(){}

void DigDugGame::LoadGame() const
{
	//set fixed time in GameTime
	dae::GameTime::GetInstance().SetFixedElapsed(std::chrono::duration<float>(std::chrono::milliseconds(GetMs())).count());
	InputManager::GetInstance().Initialize();
	ServiceLocator::Init();

	//Set game scenes here
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<StartScreen>());
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<SingleLevel>());
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<CoopLevel>());
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<VersusLevel>());
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<OptionsScreen>());
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<CreditScreen>());
	dae::SceneManager::GetInstance().SetActive("StartScreen");
}
