// LevelBuilderTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "LevelBuilder.h"

int main()
{
	LevelBuilder newLevel{ 14, 19 };
	newLevel.SetTunnel(1 + 14 * 4);
	newLevel.SetTunnel(1 + 14 * 5);
	newLevel.SetTunnel(1 + 14 * 6);
	newLevel.SetTunnel(1 + 14 * 7);
	newLevel.SetTunnel(1 + 14 * 8);
	
	newLevel.SetTunnel(7 + 14 * 2);
	newLevel.SetTunnel(7 + 14 * 3);
	newLevel.SetTunnel(7 + 14 * 4);
	newLevel.SetTunnel(7 + 14 * 5);
	newLevel.SetTunnel(7 + 14 * 6);
	newLevel.SetTunnel(7 + 14 * 7);
	newLevel.SetTunnel(7 + 14 * 8);
	newLevel.SetTunnel(7 + 14 * 9);
	newLevel.SetTunnel(6 + 14 * 9);
	newLevel.SetTunnel(8 + 14 * 9);

	newLevel.SetTunnel(2 + 14 * 12);
	newLevel.SetTunnel(3 + 14 * 12);
	newLevel.SetTunnel(4 + 14 * 12);
	newLevel.SetTunnel(5 + 14 * 12);
	newLevel.SetTunnel(6 + 14 * 12);

	newLevel.SetTunnel(9 + 14 * 4);
	newLevel.SetTunnel(10 + 14 * 4);
	newLevel.SetTunnel(11 + 14 * 4);
	newLevel.SetTunnel(12 + 14 * 4);

	newLevel.SetTunnel(9 + 14 * 11);
	newLevel.SetTunnel(9 + 14 * 12);
	newLevel.SetTunnel(9 + 14 * 13);
	newLevel.SetTunnel(9 + 14 * 14);
	newLevel.SetTunnel(9 + 14 * 15);
	newLevel.SetTunnel(9 + 14 * 16);
	newLevel.Write("Level1");
}
