#include "MiniginPCH.h"
#include "GameScene.h"



GameScene::GameScene(std::string sceneName)
	:m_SceneName(sceneName)
{
}

void GameScene::AddChild(std::shared_ptr<dae::SceneObject> obj)
{
	m_Objects.push_back(obj);
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
