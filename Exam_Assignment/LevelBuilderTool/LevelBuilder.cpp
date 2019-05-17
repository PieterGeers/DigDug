#include "pch.h"
#include "LevelBuilder.h"
#include "BinaryWriter.h"
#include <iostream>


LevelBuilder::LevelBuilder(unsigned width, unsigned height)
	:m_Width(width)
	,m_Height(height)
{
	m_Level.resize(width * height);
	for (unsigned int i = 0; i < width * height; ++i)
	{
		m_Level[i] = false;
	}
}

void LevelBuilder::SetTunnel(unsigned idx, bool add)
{
	m_Level[idx] = add;
}

void LevelBuilder::Write(std::string name)
{
	BinaryWriter writer{ name + ".bin" };
	for (bool element : m_Level)
		writer.Write<bool>(element);
	writer.CloseFile();
}

void LevelBuilder::Show()
{
	std::cout << '\t';
	for (unsigned i = 0; i < m_Width; ++i)
		std::cout << i << '\t';
	std::cout << std::endl;
	for (unsigned i = 0; i < m_Height; ++i)
	{
		std::cout << i << '\t';
		for (unsigned j = 0; j < m_Width; ++j)
		{
			if (!m_Level[i*m_Width + j])
				std::cout << 'O' << '\t';
			else
				std::cout << 'X' << '\t';
		}
		std::cout << std::endl;
	}
}
