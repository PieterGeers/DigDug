#include "MiniginPCH.h"
#include "Debug.h"
#include "InputManager.h"
#include <SDL.h>

void Debug::Log(LogLevel level, const std::string& text)
{
	switch (level)
	{
	case Warning:
		LogWarning(text);
		break;
	case Error:
		LogError(text);
		break;
	}
}

void Debug::LogWarning(const std::string& warning)
{
	const SDL_MessageBoxButtonData buttons[] = {
		{SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,1,"Continue"},
		{SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Quit"}
	};
	const SDL_MessageBoxColorScheme colorScheme = { {
			/* [BACKGROUND] */
			{ 255,   255,   255 },
			/* [COLOR_TEXT] */
			{   0, 0,   0 },
			/* [COLOR_BUTTON_BORDER] */
			{ 150, 150,   150 },
			/* [COLOR_BUTTON_BACKGROUND] */
			{   200,   200, 200 },
			/* [COLOR_BUTTON_SELECTED] */
			{ 255,   255, 255 }
		} };

	const SDL_MessageBoxData messageBoxData = {
	SDL_MESSAGEBOX_INFORMATION, /* .flags */
	nullptr, /* .window */
	"Warning", /* .title */
	warning.c_str(), /* .message */
	SDL_arraysize(buttons), /* .numbuttons */
	buttons, /* .buttons */
	&colorScheme /* .colorScheme */
	};
	int buttonID;
	if (SDL_ShowMessageBox(&messageBoxData, &buttonID) < 0) {
		SDL_Log("error displaying message box");
	}
	if (buttonID == 0)
		InputManager::GetInstance().Quit();
}

void Debug::LogError(const std::string& error)
{
	const SDL_MessageBoxButtonData buttons[] = {
	{SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Quit"}
	};
	const SDL_MessageBoxColorScheme colorScheme = { {
			/* [BACKGROUND] */
			{ 255,   255,   255 },
			/* [COLOR_TEXT] */
			{   0, 0,   0 },
			/* [COLOR_BUTTON_BORDER] */
			{ 150, 150,   150 },
			/* [COLOR_BUTTON_BACKGROUND] */
			{   200,   200, 200 },
			/* [COLOR_BUTTON_SELECTED] */
			{ 255,   255, 255 }
		} };

	std::string Error = std::move(error) + "\n\nQuit will quit the application";

	const SDL_MessageBoxData messageBoxData = {
	SDL_MESSAGEBOX_INFORMATION, /* .flags */
	nullptr, /* .window */
	"Error", /* .title */
	Error.c_str(), /* .message */
	SDL_arraysize(buttons), /* .numbuttons */
	buttons, /* .buttons */
	&colorScheme /* .colorScheme */
	};
	int buttonID;
	if (SDL_ShowMessageBox(&messageBoxData, &buttonID) < 0) {
		SDL_Log("error displaying message box");
	}
	if (buttonID == 0)
		InputManager::GetInstance().Quit();

}

bool Debug::CompareStringLeft(const std::string& toCheck, const std::string& checkWith, unsigned forAmountOfChar)
{
	const auto substr1 = toCheck.substr(0, forAmountOfChar);
	const auto substr2 = checkWith.substr(0, forAmountOfChar);
	return substr1 == substr2;
}
