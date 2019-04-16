#include "MiniginPCH.h"
#include "SceneManager.h"


//void dae::SceneManager::Update()
//{
//	for (auto scene : mScenes)
//	{
//		scene->Update();
//	}
//}
//
//void dae::SceneManager::FixedUpdate()
//{
//	for (auto scene : mScenes)
//	{
//		scene->FixedUpdate();
//	}
//}
//
//void dae::SceneManager::Render()
//{
//	for (const auto scene : mScenes)
//	{
//		scene->Render();
//	}
//}
//
//dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
//{
//	const auto scene = std::shared_ptr<Scene>(new Scene(name));
//	mScenes.push_back(scene);
//	return *scene;
//}

void dae::SceneManager::AddGameScene(std::shared_ptr<GameScene> scene)
{
	const auto it = std::find(m_Scenes.begin(), m_Scenes.end(), scene);
	if (it != m_Scenes.end())
		return;
	m_Scenes.push_back(scene);
	if (m_CurrentScene == nullptr)
		m_CurrentScene = scene;
}

void dae::SceneManager::SetActive(std::string name)
{
	for (auto scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			m_CurrentScene = scene;
			m_CurrentScene->Initialize();
			return;
		}
	}
}

void dae::SceneManager::Update()
{
	if (m_CurrentScene != nullptr)
	{
		m_CurrentScene->RootUpdate();
		m_CurrentScene->Update();
	}
}

void dae::SceneManager::FixedUpdate()
{
	if (m_CurrentScene != nullptr)
	{
		m_CurrentScene->RootFixedUpdate();
		m_CurrentScene->FixedUpdate();
	}
}

void dae::SceneManager::Render() const
{
	if (m_CurrentScene != nullptr)
	{
		m_CurrentScene->RootRender();
		m_CurrentScene->Render();
	}
}

dae::SceneManager::SceneManager()
{
}
