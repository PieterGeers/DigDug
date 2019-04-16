#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

bool PlayerInput::ProcessInput(int id)
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(id, &currentState);
	SDL_Event e;
	while(SDL_PollEvent(&e)) //THIS IS NECESSARY >_<
	{
		if (e.type == SDL_QUIT) {return false;}
	}
	if (IsPressed(ControllerButton::ButtonX)) { return false; }
	return true;
}

bool PlayerInput::IsPressed(ControllerButton button) const
{
	return (DWORD(button) & currentState.Gamepad.wButtons) != 0;
}

void PlayerInput::SetButton(const ControllerButton& button, std::shared_ptr<Command> command)
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		m_A = command;
		break;
	case ControllerButton::ButtonX:
		m_X = command;
		break;
	case ControllerButton::Down:
		m_Down = command;
		break;
	case ControllerButton::Left:
		m_Left = command;
		break;
	case ControllerButton::Right:
		m_Right = command;
		break;
	case ControllerButton::Up:
		m_Up = command;
		break;
	}
}

std::shared_ptr<Command> PlayerInput::GetCommand(const ControllerButton& button)
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_A;
	case ControllerButton::ButtonX:
		return m_X;
	case ControllerButton::Down:
		return m_Down;
	case ControllerButton::Left:
		return m_Left;
	case ControllerButton::Right:
		return m_Right;
	case ControllerButton::Up:
		return m_Up;
	default:
		return std::make_shared<NullCommand>();
	}
}