#pragma once
#include "Singleton.h"
#include "GameScene.h"

namespace dae
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager() = default;

		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) = delete;

		void AddGameScene(std::shared_ptr<GameScene> scene);
		void SetActive(std::string name);

		void Update();
		void FixedUpdate();
		void Render() const;

		std::shared_ptr<GameScene> GetGameScene(const std::string& name);

	private:
		SceneManager();
		friend class Singleton<SceneManager>;

		std::vector<std::shared_ptr<GameScene>> m_Scenes{};
		std::shared_ptr<GameScene> m_CurrentScene;
	};
}
