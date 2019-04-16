#pragma once
#include "Scene.h"
#include "GameObject.h"

class Level final : public GameScene
{
public:
	Level();
	virtual ~Level() = default;

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

private:
	std::shared_ptr<dae::GameObject> m_DigDug;
};

