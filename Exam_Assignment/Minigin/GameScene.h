#pragma once
#include "SceneObject.h"

class GameScene
{
public:
	GameScene(std::string sceneName);
	virtual ~GameScene() = default;

	GameScene(const GameScene& other) = delete;
	GameScene(GameScene&& other) = delete;
	GameScene& operator=(const GameScene& other) = delete;
	GameScene& operator=(GameScene&& other) = delete;

	void AddChild(std::shared_ptr<SceneObject> obj);
	void RemoveChild(std::shared_ptr<SceneObject> obj);

	std::string GetName() const { return m_SceneName; }

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Render() const = 0;

	void RootUpdate();
	void RootFixedUpdate();
	void RootRender() const;

protected:
	void ClearGameObjects();

private:
	std::vector<std::shared_ptr<SceneObject>> m_Objects{};
	std::string m_SceneName;
};

