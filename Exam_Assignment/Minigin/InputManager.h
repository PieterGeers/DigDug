#pragma once
#include <XInput.h>
#include "Command.h"

enum class ControllerButton
{
	ButtonA = XINPUT_GAMEPAD_A,
	ButtonX = XINPUT_GAMEPAD_X,
	Up = XINPUT_GAMEPAD_DPAD_UP,
	Down = XINPUT_GAMEPAD_DPAD_DOWN,
	Left = XINPUT_GAMEPAD_DPAD_LEFT,
	Right = XINPUT_GAMEPAD_DPAD_RIGHT
};

class Input
{
public:
	virtual ~Input() = default;
	virtual bool ProcessInput(int) = 0;
	virtual bool IsPressed(ControllerButton) const = 0;
	virtual void SetButton(const ControllerButton&, std::shared_ptr<Command>) = 0;
	virtual std::shared_ptr<Command> GetCommand(const ControllerButton&) = 0;
};

class NullInput final : public Input
{
public:
	bool ProcessInput(int) override { return false; };
	bool IsPressed(ControllerButton) const override { return false; }
	void SetButton(const ControllerButton&, std::shared_ptr<Command>) override = 0;
	std::shared_ptr<Command> GetCommand(const ControllerButton&) override = 0;
};

class PlayerInput final : public Input
{
public:
	bool ProcessInput(int id) override;
	bool IsPressed(ControllerButton button) const override;
	void SetButton(const ControllerButton& button, std::shared_ptr<Command> command) override;
	std::shared_ptr<Command> GetCommand(const ControllerButton& button) override;
private:
	_XINPUT_STATE currentState{};
	std::shared_ptr<Command> 
	m_A = std::make_shared<NullCommand>(), 
	m_X = std::make_shared<NullCommand>(), 
	m_Up = std::make_shared<NullCommand>(),
	m_Down = std::make_shared<NullCommand>(),
	m_Left = std::make_shared<NullCommand>(),
	m_Right = std::make_shared<NullCommand>();
};
