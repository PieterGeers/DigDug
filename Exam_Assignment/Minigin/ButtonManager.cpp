#include "MiniginPCH.h"
#include "ButtonManager.h"



ButtonManager::ButtonManager()
{
}

void ButtonManager::SetStartButtonByIdx(unsigned idx)
{
	if (!m_Buttons[idx])
		return;
	const auto component = m_Buttons[idx]->GetComponent<ButtonComponent>();
	if (component == nullptr)
		return;
	component->HooverOver(SDL_Color{ 255,255,255,255 });
	m_CurrentIdx = idx;
}

void ButtonManager::ButtonDown()
{
	auto component = m_Buttons[m_CurrentIdx]->GetComponent<ButtonComponent>();
	if (component == nullptr)
		return;
	component->ResetColor();
	++m_CurrentIdx;
	if (m_CurrentIdx >= int(m_Buttons.size()))
		m_CurrentIdx = 0;
	component = m_Buttons[m_CurrentIdx]->GetComponent<ButtonComponent>();
	if (component == nullptr)
		return;
	component->HooverOver(SDL_Color{ 255,255,255,255 });
}

std::shared_ptr<ButtonComponent> ButtonManager::GetActiveButtonComp()
{
	return m_Buttons[m_CurrentIdx]->GetComponent<ButtonComponent>();
}

void ButtonManager::ButtonUp()
{
	auto component = m_Buttons[m_CurrentIdx]->GetComponent<ButtonComponent>();
	if (component == nullptr)
		return;
	component->ResetColor();
	--m_CurrentIdx;
	if (m_CurrentIdx < 0)
		m_CurrentIdx = int(m_Buttons.size()) - 1;
	component = m_Buttons[m_CurrentIdx]->GetComponent<ButtonComponent>();
	if (component == nullptr)
		return;
	component->HooverOver(SDL_Color{ 255,255,255,255 });
}

