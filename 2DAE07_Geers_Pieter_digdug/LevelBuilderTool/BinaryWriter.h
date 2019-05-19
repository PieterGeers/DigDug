#pragma once
#include <string>
#include <fstream>

class BinaryWriter
{
public:
	BinaryWriter(const std::string& filepath);
	~BinaryWriter() = default;

	template<typename T>
	void Write(T value)
	{
		m_Writer.write((char*)&value, sizeof(T));
	}

	void CloseFile();
private:
	std::ofstream m_Writer;
	bool m_Exists = false;
};
