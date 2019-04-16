#include "pch.h"
#include "LevelBuilder.h"
#include "BinaryWriter.h"


LevelBuilder::LevelBuilder(unsigned width, unsigned height)
{
	m_Level.resize(width * height);
	for (unsigned int i = 0; i < width * height; ++i)
	{
		m_Level[i] = false;
	}
}

void LevelBuilder::SetTunnel(unsigned idx)
{
	m_Level[idx] = true;
}

void LevelBuilder::Write(std::string name)
{
	BinaryWriter writer{ name + ".bin" };
	for (bool element : m_Level)
		writer.Write<bool>(element);
	writer.CloseFile();
}
