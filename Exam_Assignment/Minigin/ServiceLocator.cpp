#include "MiniginPCH.h"
#include "ServiceLocator.h"

std::shared_ptr<GameObject> ServiceLocator::m_pPlayer1;
std::shared_ptr<GameObject> ServiceLocator::m_pPlayer2;
//std::shared_ptr<dae::GameObject> ServiceLocator::m_pPlayer3;
//std::shared_ptr<dae::GameObject> ServiceLocator::m_pPlayer4;
std::shared_ptr<GameObject> ServiceLocator::m_pDefaultGameObject;

std::shared_ptr<ButtonManager> ServiceLocator::m_pButtonManager;
std::shared_ptr<ButtonManager> ServiceLocator::m_pDefaultButtonManager;