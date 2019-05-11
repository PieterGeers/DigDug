#include "MiniginPCH.h"
#include "ServiceLocator.h"


std::shared_ptr<ButtonManager> ServiceLocator::m_pButtonManager;
std::shared_ptr<ButtonManager> ServiceLocator::m_pDefaultButtonManager;

std::map<int, std::shared_ptr<GameObject>> ServiceLocator::m_pPlayers;
std::map<int, std::shared_ptr<GameObject>> ServiceLocator::m_pAgents;