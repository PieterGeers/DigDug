#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameTime.h"
#include "ServiceLocator.h"
#include "LevelComponent.h"
#include "Level.h"
#include "StartScreen.h"


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		448,
		608,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	std::shared_ptr<Input> service = std::make_shared<PlayerInput>();
	ServiceLocator::RegisterInputP1Service(service);
	ServiceLocator::RegisterInputP2Service(nullptr);

	//set fixed time in GameTime
	GameTime::GetInstance().SetFixedElapsed(std::chrono::duration<float>(std::chrono::milliseconds(msPerFrame)).count());

	//Set game scenes here
	SceneManager::GetInstance().AddGameScene(std::make_shared<StartScreen>());
	SceneManager::GetInstance().AddGameScene(std::make_shared<Level>());
	SceneManager::GetInstance().SetActive("StartScene");
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& p1Input = ServiceLocator::GetInputP1();
		auto& p2Input = ServiceLocator::GetInputP2();
		auto& time = GameTime::GetInstance();


		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			time.SetDeltaT(std::chrono::duration<float>(currentTime - lastTime).count());
			lastTime = currentTime;
			lag += time.DeltaT() * 1000;

			if (&p1Input != nullptr)
				doContinue = p1Input.ProcessInput(0);
			if (&p2Input != nullptr)
				p2Input.ProcessInput(1);

			while (lag >= msPerFrame)
			{
				sceneManager.FixedUpdate();
				lag -= msPerFrame;
			}

			sceneManager.Update();
			renderer.Render();
		}
	}

	Cleanup();
}
