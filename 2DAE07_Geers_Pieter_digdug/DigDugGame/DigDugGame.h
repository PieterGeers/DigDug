#pragma once
#include "Minigin.h"

class DigDugGame : public dae::Minigin
{
public:
	DigDugGame(void);
	~DigDugGame(void);
	void LoadGame() const override;
};

