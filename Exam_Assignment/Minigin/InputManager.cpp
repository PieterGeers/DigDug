#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

bool dae::PlayerInput::ProcessInput(int id)
{
	XInputGetState(id, &currentState);
	return !((DWORD(ControllerButton::ButtonX) & currentState.Gamepad.wButtons) != 0);
}

bool dae::PlayerInput::IsPressed(ControllerButton button) const
{
	return (DWORD(button) & currentState.Gamepad.wButtons) != 0;
}
