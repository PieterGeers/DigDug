#pragma once
#include "Structs.h"

struct DigDugCell final : public Cell
{
	DigDugCell(unsigned idx, const MVector2_INT& position, bool can_walk_on, bool has_visited, bool has_stone)
		: Cell(idx, position, can_walk_on),
		  hasVisited(has_visited),
		  hasStone(has_stone)
	{
	}
	DigDugCell(){}
	bool hasVisited = false;
	bool hasStone = false;
};