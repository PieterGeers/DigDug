#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Structs.h"
#include <map>
#pragma comment(lib,"xinput.lib")

class Command;

class InputManager : public dae::Singleton<InputManager>
{
public:
	void Initialize();
	bool ProcessInput();
	void Update();
	bool IsPressed( int actionID);
	void SetCommand( int actionID, std::shared_ptr<Command> command);
	void AddInputAction(const InputAction& action, const std::shared_ptr<Command>& command);
	void RefreshControllerConnections();
	void ResetInput();
	void CleanUp() const;
	void Quit() {m_Quit = false;}
private:
	std::map<int, InputAction> m_Actions;
	std::map<int, std::shared_ptr<Command>> m_Commands;
	BYTE *m_pCurrKeyboardState = nullptr, *m_pOldKeyboardState = nullptr, *m_pKeyboardState0 = nullptr, *m_pKeyboardState1 = nullptr;
	bool m_KeyboardState0Active = true, m_HasReset = false;
	XINPUT_STATE m_OldGamepadState[XUSER_MAX_COUNT]{}, m_CurrGamepadState[XUSER_MAX_COUNT]{};
	bool m_ConnectedGamepads[XUSER_MAX_COUNT]{};
	bool m_Quit = true;

	void UpdateGamePadStates();
	bool UpdateKeyboardState();
	bool IsKeyboardKeyDown(int key, bool previousFrame = false) const;
	bool IsGamePadButtonDown(WORD button, GamepadIndex playerIndex, bool previousFrame = false);
};