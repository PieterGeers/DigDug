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
#include "TransformComponent.h"
#include "TextureRenderComponent.h"


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
	std::shared_ptr<TransformComponent> go_transform = std::make_shared<TransformComponent>();
	go_transform->SetPosition(216, 180, 0);
	go_texture = std::make_shared<TextureRenderComponent>("logo.png");
	go_texture->SetPosition(go_transform->GetPosition().x, go_transform->GetPosition().y);
	go->AddComponent(go_transform);
	go->AddComponent(go_texture);
	scene.Add(go);

	auto to = std::make_shared<GameObject>();
	std::shared_ptr<TransformComponent> to_transform = std::make_shared<TransformComponent>();
	std::shared_ptr<TextRenderComponent> to_text = std::make_shared<TextRenderComponent>("Programming 4 Assignment", font);
	to_transform->SetPosition(80, 20, 0);
	to_text->SetPosition(to_transform->GetPosition().x, to_transform->GetPosition().y);
	to->AddComponent(to_transform);
	to->AddComponent(to_text);
	scene.Add(to);

	auto fpsCounter = std::make_shared<GameObject>();
	std::shared_ptr<FPSComponent> fps_component = std::make_shared<FPSComponent>(fpsFont, SDL_Color{153,153,0,255});
	std::shared_ptr<TransformComponent> fps_transform = std::make_shared<TransformComponent>();
	fps_transform->SetPosition(0, 0, 0);
	fps_component->SetPosition(fps_transform->GetPosition().x, fps_transform->GetPosition().y);
	fpsCounter->AddComponent(fps_component);
	fpsCounter->AddComponent(fps_transform);
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
		auto t = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
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

			doContinue = input.ProcessInput();

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
