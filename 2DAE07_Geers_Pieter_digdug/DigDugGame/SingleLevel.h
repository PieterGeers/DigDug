#pragma once
#include "GameScene.h"

class SingleLevel final : public GameScene
{
public:
	SingleLevel();
	~SingleLevel() = default;

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

private:
	int m_CurrentLevel = 1;
	void ResetScene();
	void ReloadScene();
};

