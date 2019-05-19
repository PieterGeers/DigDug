#pragma once
#include <vector>

class LevelBuilder
{
public:
	LevelBuilder(unsigned width, unsigned height);
	~LevelBuilder() = default;

	void SetTunnel(unsigned idx, bool add = true);
	void Write(std::string name);
	void Show();
private:
	std::vector<bool> m_Level;
	unsigned m_Width = 0, m_Height = 0;
};

