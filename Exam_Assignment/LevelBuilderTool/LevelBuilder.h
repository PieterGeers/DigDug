#pragma once
#include <vector>

class LevelBuilder
{
public:
	LevelBuilder(unsigned width, unsigned height);
	~LevelBuilder() = default;

	void SetTunnel(unsigned idx);
	void Write(std::string name);

private:
	std::vector<bool> m_Level;
};

