#pragma once
#include "GameObject.h"
#include "GameScene.h"
#include "Node.h"

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
	std::shared_ptr<GameObject> m_DigDug;
	std::shared_ptr<Node> node;
};

