#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include <iterator>
#include "Command.h"

//==============================================================================//
// I took a lot of inspiration for this class from OverlordEngine::InputManager //
// Credits go to OverlordEngine::InputManager creator							//
//==============================================================================//
void InputManager::Initialize()
{
	m_pKeyboardState0 = new BYTE[256];
	m_pKeyboardState1 = new BYTE[256];

	GetKeyboardState(m_pKeyboardState0);
	GetKeyboardState(m_pKeyboardState1);

	RefreshControllerConnections();
}

void InputManager::Update()
{
	UpdateKeyboardState();
	UpdateGamePadStates();

	for (auto it = m_Actions.begin(); it != m_Actions.end(); ++it)
	{
		const auto currAction = &(it->second);
		currAction->IsTriggered = false;

		switch (currAction->TriggerState) 
		{ 
		case Pressed:
			//KEYBOARD
			if (!IsKeyboardKeyDown(currAction->KeyboardCode, true) && IsKeyboardKeyDown(currAction->KeyboardCode))
				currAction->IsTriggered = true;
			//GAMEPAD
			if (!IsGamePadButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex, true) && IsGamePadButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex))
				currAction->IsTriggered = true;

			break;

		case Released:
			//KEYBOARD
			if (IsKeyboardKeyDown(currAction->KeyboardCode, true) && !IsKeyboardKeyDown(currAction->KeyboardCode))
				currAction->IsTriggered = true;
			//GAMEPAD
			if (IsGamePadButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex, true) && !IsGamePadButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex))
				currAction->IsTriggered = true;

			break;

		case Down:
			//KEYBOARD
			if (IsKeyboardKeyDown(currAction->KeyboardCode, true) && IsKeyboardKeyDown(currAction->KeyboardCode))
				currAction->IsTriggered = true;
			//GAMEPAD
			if (IsGamePadButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex, true) && IsGamePadButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex))
				currAction->IsTriggered = true;

			break;
		}
	}
}

void InputManager::UpdateGamePadStates()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (!m_ConnectedGamepads[i])
			return;

		m_OldGamepadState[i] = m_CurrGamepadState[i];

		const DWORD dwResult = XInputGetState(i, &m_CurrGamepadState[i]);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}

void InputManager::RefreshControllerConnections()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		const DWORD dwResult = XInputGetState(i, &state);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}

bool InputManager::UpdateKeyboardState()
{
	//m_pOldKeyboardState = m_pCurrKeyboardState;
	//GetKeyboardState(m_pCurrKeyboardState);
	BOOL getKeyboardResult;
	if (m_KeyboardState0Active)
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardState1);
		m_pOldKeyboardState = m_pKeyboardState0;
		m_pCurrKeyboardState = m_pKeyboardState1;
	}
	else
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardState0);
		m_pOldKeyboardState = m_pKeyboardState1;
		m_pCurrKeyboardState = m_pKeyboardState0;
	}

	m_KeyboardState0Active = !m_KeyboardState0Active;

	return getKeyboardResult > 0;

}

bool InputManager::IsKeyboardKeyDown(int key, bool previousFrame) const
{
	if (!m_pCurrKeyboardState || !m_pOldKeyboardState)
		return false;

	if (key > 0x07 && key <= 0xFE)
	{
		if (previousFrame)
			return (m_pOldKeyboardState[key] & 0xF0) != 0;
		return (m_pCurrKeyboardState[key] & 0xF0) != 0;
	}

	return false;
}

bool InputManager::IsGamePadButtonDown(WORD button, GamepadIndex playerIndex, bool previousFrame)
{
	if (button > 0x0000 && button <= 0x8000)
	{
		if (!m_ConnectedGamepads[playerIndex])
			return false;
		if (previousFrame)
			return (m_OldGamepadState[playerIndex].Gamepad.wButtons&button) != 0;
		return (m_CurrGamepadState[playerIndex].Gamepad.wButtons&button) != 0;
	}

	return false;
}

bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) //THIS IS NECESSARY >_<
	{
		if (e.type == SDL_QUIT) {return false;}
	}
	Update();
	for (auto it = m_Commands.begin(); it != m_Commands.end();)
	{
		if (IsPressed(it->first))
			it->second->Execute();
		if (!m_HasReset) { ++it; }
		else { m_HasReset = false; break; }
	}
	return m_Quit;
}

bool InputManager::IsPressed(int actionID)
{
	return m_Actions[actionID].IsTriggered;
}

void InputManager::SetCommand(int actionID, std::shared_ptr<Command> command)
{
	const auto it = m_Actions.find(actionID);
	if (it == m_Actions.end())
		Debug::LogError("InputManager::SetCommand : Could not bind command");
	m_Commands[actionID] = command;
}

void InputManager::AddInputAction(const InputAction& action, const std::shared_ptr<Command>& command)
{
	const auto it = m_Actions.find(action.ActionID);
	if (it != m_Actions.end()) 
		return;

	m_Actions[action.ActionID] = action;
	m_Commands[action.ActionID] = command;

}

void InputManager::ResetInput()
{
	m_HasReset = true;
	m_Commands.clear();
	m_Actions.clear();
}

void InputManager::CleanUp() const
{
	if (m_pKeyboardState0 != nullptr)
	{
		delete[] m_pKeyboardState0;
		delete[] m_pKeyboardState1;
	}
}
