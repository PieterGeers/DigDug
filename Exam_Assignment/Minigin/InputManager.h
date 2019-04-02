#pragma once
#include <XInput.h>

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
	virtual bool ProcessInput(int id) = 0;
	virtual bool IsPressed(ControllerButton button) const = 0;
};

class NullInput final : public Input
{
public:
	bool ProcessInput(int) override { return false; };
	bool IsPressed(ControllerButton) const override { return false; }
};

class PlayerInput final : public Input
{
public:
	bool ProcessInput(int id) override;
	bool IsPressed(ControllerButton button) const override;
private:
	_XINPUT_STATE currentState{};
};
