#pragma once
#include "GameScene.h"
#include "GameObject.h"

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
	std::shared_ptr<dae::GameObject> m_DigDug;
};

