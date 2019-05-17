#pragma once
#include "GameScene.h"

class VersusLevel final : public GameScene
{
public:
	VersusLevel();
	virtual ~VersusLevel() = default;

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

private:
	int m_CurrentLevel = 1;
	void ResetScene();
	void ReloadScene();

};

