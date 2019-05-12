#pragma once
#include "ButtonManager.h"
#include "CharacterComponent.h"
#include "Debug.h"
#include <map>

class ServiceLocator
{
public:
	static void Init()
	{
		m_pButtonManager = m_pDefaultButtonManager;
	}
	static void RegisterPlayer(int Id, std::shared_ptr<GameObject>& service)
	{
		if (!service->HasComponentDerived<CharacterComponent>())
			Debug::LogError("RegisterService::Player1 : service does not have CharacterComponent");
		m_pPlayers[Id] = service;
	}
	static void RegisterAgent(int Id, std::shared_ptr<GameObject>& service)
	{
		m_pAgents.insert({ Id, service });
	}

	static void RegisterButtonManager(std::shared_ptr<ButtonManager> service) { m_pButtonManager = (service == nullptr) ? m_pDefaultButtonManager : service; }

	static std::shared_ptr<GameObject>& GetPlayer(int id) { return m_pPlayers.find(id)->second; }
	static std::map<int, std::shared_ptr<GameObject>>& GetPlayers() { return m_pPlayers; }

	static std::shared_ptr<GameObject>& GetAgent(int id) { return m_pAgents.find(id)->second; }
	static std::map<int, std::shared_ptr<GameObject>>& GetAgents() { return m_pAgents; }

	static std::shared_ptr<ButtonManager>& GetButtonManager() { return m_pButtonManager; }
	
private:
	static std::shared_ptr<ButtonManager> m_pButtonManager;
	static std::shared_ptr<ButtonManager> m_pDefaultButtonManager;
	static std::map<int, std::shared_ptr<GameObject>> m_pPlayers;
	static std::map<int, std::shared_ptr<GameObject>> m_pAgents;
};

