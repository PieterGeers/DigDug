#include "pch.h"
#include "BinaryWriter.h"
#include <iostream>


BinaryWriter::BinaryWriter(const std::string& filepath)
	: m_Writer(std::ofstream(filepath.c_str(), std::ios::out | std::ios::binary))
{
	if (m_Writer.is_open()) m_Exists = true;
	else
	{
		std::cout << "[WRITE] Failed to open file: " << filepath << std::endl;
	}
}

void BinaryWriter::CloseFile()
{
	m_Exists = false;
	m_Writer.close();
}

