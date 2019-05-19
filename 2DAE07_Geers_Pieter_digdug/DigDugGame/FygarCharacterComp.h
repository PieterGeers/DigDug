#pragma once
#include "CharacterComponent.h"

class FygarCharacterComp final : public CharacterComponent
{
public:
	FygarCharacterComp(Boundaries levelBounds, int index);
	~FygarCharacterComp() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void SetTransform(float, float, float) override;
	void MoveRight(float amount) override;
	void MoveUp(float amount) override;

	void SetIsPlayerInvisible(bool isInvis) { m_IsInvisible = isInvis; }
	bool GetIsPlayerInvisible() const { return m_IsInvisible; }
	bool GetIsMovingAutomatic() const { return m_IsMoveAutomatic; }
	void SetIsMovingAutomatic(bool isMovingAuto) { m_IsMoveAutomatic = isMovingAuto; }


	void ExecuteMovement(Direction dir);
	void FreezeForTime(float time);
	bool GetIsFreeze() const { return m_Freeze; }
	bool GetIsDead() const { return m_IsDead; }
	void SetDead() { m_IsDead = true; }

	int GetIndex() const { return m_Index; }

private:
	float m_FreezeTime = 0.0f;
	bool m_Freeze = false;
	bool m_CanMove = true;
	bool m_IsInvisible = false;
	bool m_IsMoveAutomatic = false;
	bool m_IsDead = false;
	int m_Index = 0;

};

