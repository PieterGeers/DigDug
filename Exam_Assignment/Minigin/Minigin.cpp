#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "GameTime.h"
#include "FPSComponent.h"
#include "TextRenderComponent.h"
#include "TextureRenderComponent.h"
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
		640,
		480,
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
	//ServiceLocator::RegisterInputP2Service(nullptr);

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	//set fixed time in GameTime
	GameTime::GetInstance().SetFixedElapsed(std::chrono::duration<float>(std::chrono::milliseconds(msPerFrame)).count());

	auto go = std::make_shared<GameObject>();
	std::shared_ptr<TextureRenderComponent> go_texture = std::make_shared<TextureRenderComponent>("background.jpg");
	go->AddComponent(go_texture);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go_texture = std::make_shared<TextureRenderComponent>("logo.png");
	go->AddComponent(go_texture);
	go->SetPosition(216, 180, 0);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go_texture = std::make_shared<TextureRenderComponent>("digdug_spriteP1.png", 7, 7, 3);
	go_texture->SetSpritePosition(0, 0, 6, 6);
	go->AddComponent(go_texture);
	go->SetPosition(216, 100, 0);
	scene.Add(go);


	auto to = std::make_shared<GameObject>();
	std::shared_ptr<TextRenderComponent> to_text = std::make_shared<TextRenderComponent>("Programming 4 Assignment", font);
	to->AddComponent(to_text);
	to->SetPosition(80, 20, 0);
	scene.Add(to);

	auto fpsCounter = std::make_shared<GameObject>();
	std::shared_ptr<FPSComponent> fps_component = std::make_shared<FPSComponent>(fpsFont, SDL_Color{ 153,153,0,255 });
	fpsCounter->AddComponent(fps_component);
	scene.Add(fpsCounter);
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
			lag += time.DeltaT();

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
