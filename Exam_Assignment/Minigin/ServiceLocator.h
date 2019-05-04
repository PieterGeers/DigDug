#pragma once
#include "ButtonManager.h"
#include "CharacterComponent.h"
#include "Debug.h"

class ServiceLocator
{
public:
	static void Init()
	{
		m_pPlayer1 = m_pDefaultGameObject;
		m_pPlayer2 = m_pDefaultGameObject;
		m_pButtonManager = m_pDefaultButtonManager;
	}
	static void RegisterP1Service(std::shared_ptr<GameObject>& service)
	{
		if (!service->HasComponentDerived<CharacterComponent>())
			Debug::LogError("RegisterService::Player1 : service does not have CharacterComponent");
		m_pPlayer1 = (service == nullptr) ? m_pDefaultGameObject : service;
	}
	static void RegisterP2Service(std::shared_ptr<GameObject>& service)
	{
		if (!service->HasComponentDerived<CharacterComponent>())
			Debug::LogError("RegisterService::Player2 : service does not have CharacterComponent");
		m_pPlayer2 = (service == nullptr) ? m_pDefaultGameObject : service;
	}

	static void RegisterButtonManager(std::shared_ptr<ButtonManager> service) { m_pButtonManager = (service == nullptr) ? m_pDefaultButtonManager : service; }


	static std::shared_ptr<GameObject>& GetP1() { return m_pPlayer1; }
	static std::shared_ptr<GameObject>& GetP2() { return m_pPlayer2; }
	static std::shared_ptr<ButtonManager>& GetButtonManager() { return m_pButtonManager; }

private:
	static std::shared_ptr<GameObject> m_pPlayer1;
	static std::shared_ptr<GameObject> m_pPlayer2;
	static std::shared_ptr<GameObject> m_pDefaultGameObject;
	static std::shared_ptr<ButtonManager> m_pButtonManager;
	static std::shared_ptr<ButtonManager> m_pDefaultButtonManager;
};

