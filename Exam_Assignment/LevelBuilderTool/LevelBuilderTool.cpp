// LevelBuilderTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "LevelBuilder.h"

int main()
{
	int width = 0;
	int height = 0;
	int posX = 0, posY = 0;

	std::string name{ "" };
	std::string function{ "" };

	std::cout << "\t\t--===LevelBuilder===--" << std::endl;
	std::cout << "Functions: " << std::endl;
	std::cout << "Use 'Add posX posY' to add a new tunnel" << std::endl;
	std::cout << "Use 'Remove posX posY' to remove a tunnel" << std::endl;
	std::cout << "Use 'Print 0 0' to show the level" << std::endl;
	std::cout << "Use 'Close 0 0' to create the binary file" << std::endl;
	std::cout << "\t\t--==================--" << std::endl;

	std::cout << "Give me the amount of columns (width) in the level: ";
	std::cin >> width;
	std::cout << "Give me the amount of row (height) in the level: ";
	std::cin >> height;
	std::cout << "Give me the name of the new file: ";
	std::cin >> name;
	if (width <= 0 || height <= 0)
	{
		std::cout << "width or height is less than or equal to 0 and is not allowed" << std::endl;
		return 0;
	}

	LevelBuilder newLevel{ static_cast<unsigned>(width), static_cast<unsigned>(height) };

	while (function == "Close")
	{
		std::cout << ">> ";
		std::cin >> function >> posX >> posY;
		if (function == "Add")
		{
			if (posX < width && posY < height)
				newLevel.SetTunnel(posY*width + posX, true);
		}
		if (function == "Remove")
		{
			if (posX < width && posY < height)
				newLevel.SetTunnel(posY*width + posX, false);
		}
		if (function == "Print")
		{
			newLevel.Show();
		}
	}

	newLevel.Write(name);
	return 0;
}
