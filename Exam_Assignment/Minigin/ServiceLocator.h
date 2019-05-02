#pragma once
#include "ButtonManager.h"

class ServiceLocator
{
public:
	static void Init()
	{
		m_pPlayer1 = m_pDefaultGameObject;
		m_pPlayer2 = m_pDefaultGameObject;
		//m_pPlayer3 = m_pDefaultGameObject;
		//m_pPlayer4 = m_pDefaultGameObject;
		m_pButtonManager = m_pDefaultButtonManager;
	}
	static void RegisterP1Service(std::shared_ptr<dae::GameObject>& service) { m_pPlayer1 = (service == nullptr) ? m_pDefaultGameObject : service; }
	static void RegisterP2Service(std::shared_ptr<dae::GameObject>& service) { m_pPlayer2 = (service == nullptr) ? m_pDefaultGameObject : service; }
	//static void RegisterP3Service(std::shared_ptr<dae::GameObject> service) { m_pPlayer3 = (service == nullptr) ? m_pDefaultGameObject : service; }
	//static void RegisterP4Service(std::shared_ptr<dae::GameObject> service) { m_pPlayer4 = (service == nullptr) ? m_pDefaultGameObject : service; }
	static void RegisterButtonManager(std::shared_ptr<ButtonManager> service) { m_pButtonManager = (service == nullptr) ? m_pDefaultButtonManager : service; }

	static std::shared_ptr<dae::GameObject>& GetP1() { return m_pPlayer1; }
	static std::shared_ptr<dae::GameObject>& GetP2() { return m_pPlayer2; }
	//static std::shared_ptr<dae::GameObject>& GetP3() { return m_pPlayer3; }
	//static std::shared_ptr<dae::GameObject>& GetP4() { return m_pPlayer4; }
	static std::shared_ptr<ButtonManager>& GetButtonManager() { return m_pButtonManager; }

private:
	static std::shared_ptr<dae::GameObject> m_pPlayer1;
	static std::shared_ptr<dae::GameObject> m_pPlayer2;
	//static std::shared_ptr<dae::GameObject> m_pPlayer3;
	//static std::shared_ptr<dae::GameObject> m_pPlayer4;
	static std::shared_ptr<dae::GameObject> m_pDefaultGameObject;
	static std::shared_ptr<ButtonManager> m_pButtonManager;
	static std::shared_ptr<ButtonManager> m_pDefaultButtonManager;
};

