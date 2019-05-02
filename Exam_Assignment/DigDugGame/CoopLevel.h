#pragma once
#include "GameScene.h"
#include "GameObject.h"

class CoopLevel final : public GameScene
{
public:
	CoopLevel();
	~CoopLevel() = default;

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

private:
	std::shared_ptr<dae::GameObject> m_DigDugP1;
	std::shared_ptr<dae::GameObject> m_DigDugP2;

};

