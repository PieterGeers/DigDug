#pragma once
#include "GameScene.h"
#include "ButtonManager.h"

class StartScreen final : public GameScene
{
public:
	StartScreen();
	virtual ~StartScreen() = default;

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

private:
	std::shared_ptr<ButtonManager> m_ButtonManager;
};

