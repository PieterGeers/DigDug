#include "MiniginPCH.h"
#include "GameScene.h"
#include <algorithm> 


GameScene::GameScene(std::string sceneName)
	:m_SceneName(sceneName)
{
}

void GameScene::AddChild(std::shared_ptr<SceneObject> obj)
{
	m_Objects.push_back(obj);
}

void GameScene::RemoveChild(std::shared_ptr<SceneObject> obj)
{
	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), obj), m_Objects.end());
}

void GameScene::RootUpdate()
{
	for (auto element : m_Objects)
	{
		element->Update();
	}
}

void GameScene::RootFixedUpdate()
{
	for (auto element : m_Objects)
	{
		element->FixedUpdate();
	}
}

void GameScene::RootRender() const
{
	for (const auto element : m_Objects)
	{
		element->Render();
	}
}

void GameScene::ClearGameObjects()
{
	m_Objects.clear();
}
