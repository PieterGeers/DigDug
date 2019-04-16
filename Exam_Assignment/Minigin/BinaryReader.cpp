#include "MiniginPCH.h"
#include "BinaryReader.h"

BinaryReader::BinaryReader(const std::string& readfile)
	:m_Exists(false)
	, m_Reader{ std::ifstream(readfile.c_str(), std::ios::in | std::ios::binary) }
{
	if (m_Reader.is_open()) 
		m_Exists = true;
}

void BinaryReader::CloseFile()
{
	m_Reader.close();
}