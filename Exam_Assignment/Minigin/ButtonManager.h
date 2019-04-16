#pragma once
#include "GameObject.h"

class ButtonManager final
{
public:
	ButtonManager();
	~ButtonManager() = default;

	void Update();
	void AddButton(std::shared_ptr<dae::GameObject>& button) { m_Buttons.push_back(button); }
	void SetStartButtonByIdx(unsigned int idx);

private:
	std::vector<std::shared_ptr<dae::GameObject>> m_Buttons;
	bool m_CanSwitchButton = true;
	int m_CurrentIdx = 0, m_PrevIdx = 0;
};

