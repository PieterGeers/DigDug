#include "MiniginPCH.h"
#include "ButtonManager.h"
#include "ServiceLocator.h"


ButtonManager::ButtonManager()
{
}

void ButtonManager::Update()
{
	auto& p1Input = ServiceLocator::GetInputP1();
	if (!p1Input->IsPressed(ControllerButton::Up) && !p1Input->IsPressed(ControllerButton::Down))
		m_CanSwitchButton = true;
	if (p1Input->IsPressed(ControllerButton::Up) && m_CanSwitchButton)
	{
		auto component = m_Buttons[m_CurrentIdx]->GetComponent<ButtonComponent>();
		if (component == nullptr)
			return;
		component->ResetColor();
		--m_CurrentIdx;
		if (m_CurrentIdx < 0)
			m_CurrentIdx = m_Buttons.size() - 1;
		component = m_Buttons[m_CurrentIdx]->GetComponent<ButtonComponent>();
		if (component == nullptr)
			return;
		component->HooverOver(SDL_Color{ 255,255,255,255 });
		m_CanSwitchButton = false;
	}
	else if (p1Input->IsPressed(ControllerButton::Down) && m_CanSwitchButton)
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
		m_CanSwitchButton = false;
	}
	else if (p1Input->IsPressed(ControllerButton::ButtonA))
		p1Input->GetCommand(ControllerButton::ButtonA)->Execute(m_Buttons[m_CurrentIdx]);
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

