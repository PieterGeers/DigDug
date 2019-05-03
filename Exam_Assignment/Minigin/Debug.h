#pragma once
#include "Structs.h"

class Debug
{
public:
	Debug() = default;
	~Debug() = default;

	static void Log(LogLevel level, const std::string& text);
	static void LogWarning(const std::string& warning);
	static void LogError(const std::string& error);

};

