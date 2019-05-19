#pragma once
#include <fstream>
#include <string>

class BinaryReader
{
public:
	BinaryReader(const std::string& readfile);
	~BinaryReader() = default;

	template<typename T>
	T Read()
	{
		T value{};
		if (m_Exists)
		{
			m_Reader.read((char*)&value, sizeof(T));
		}
		return value;
	}

	void CloseFile();

private:
	bool m_Exists;
	std::ifstream m_Reader;
};
