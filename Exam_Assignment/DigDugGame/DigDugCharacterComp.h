#pragma once
#include "CharacterComponent.h"

class DigDugCharacterComp final : public CharacterComponent
{
public:
	DigDugCharacterComp(std::shared_ptr<dae::GameObject>& character, Boundaries levelBounds);
	~DigDugCharacterComp() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float, float, float) override;

	void MoveRight(float amount) override;
	void MoveUp(float amount) override;

	void SetIsPlayerDigging(bool isDigging) { m_IsDigging = isDigging; }
	bool GetIsPlayerDigging() const { return m_IsDigging; }
	bool GetIsMovingAutomatic() const { return m_IsMoveAutomatic; }
	void SetIsMovingAutomatic(bool isMovingAuto) { m_IsMoveAutomatic = isMovingAuto; }

	void ExecuteMovement(Direction dir);

private:
	bool m_CanMove = true;
	bool m_IsDigging = false;
	bool m_IsMoveAutomatic = false;
	
};

