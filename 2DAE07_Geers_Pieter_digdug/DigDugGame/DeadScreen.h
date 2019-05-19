#pragma once
#include "GameScene.h"
#include "ButtonManager.h"

class DeadScreen final : public GameScene
{
public:
	DeadScreen();
	~DeadScreen() = default;

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void SetScore(int score) { m_Score = score; }

private:
	std::shared_ptr<ButtonManager> m_ButtonManager;
	int m_Score = 0;
};

