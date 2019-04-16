#pragma once
#include "Singleton.h"
#include "GameScene.h"

namespace dae
{
	//class Scene;
	//class SceneManager final : public Singleton<SceneManager>
	//{
	//public:
	//	Scene & CreateScene(const std::string& name);

	//	void Update();
	//	void FixedUpdate();
	//	void Render();

	//private:
	//	std::vector<std::shared_ptr<Scene>> mScenes;
	//};

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		virtual ~SceneManager() = default;

		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) = delete;

		void AddGameScene(std::shared_ptr<GameScene> scene);
		void SetActive(std::string name);

		void Update();
		void FixedUpdate();
		void Render() const;

	private:
		SceneManager();
		friend class Singleton<SceneManager>;

		std::vector<std::shared_ptr<GameScene>> m_Scenes{};
		std::shared_ptr<GameScene> m_CurrentScene;
	};
}
