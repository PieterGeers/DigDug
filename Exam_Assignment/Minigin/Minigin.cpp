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
#include <ctime>
#include "SoundManager.h"
#include "ServiceLocator.h"

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
	srand(int(time(nullptr)));
	Renderer::GetInstance().Init(window);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		const std::string error = Mix_GetError();
		throw std::runtime_error(error);
	}
}

void dae::Minigin::LoadGame() const
{}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	InputManager::GetInstance().CleanUp();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	SoundManager::GetInstance().Init("../Data/Sound/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& pInput = InputManager::GetInstance();
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

			doContinue = pInput.ProcessInput();

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
