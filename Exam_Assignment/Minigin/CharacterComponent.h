#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include <bitset>

struct Boundaries
{
	int top, bottom, left, right;
};

enum Direction
{
	up,
	down,
	left,
	right,
	none
};

class CharacterComponent final : public BaseComponent	
{
public:
	CharacterComponent(std::shared_ptr<dae::GameObject>& character, Boundaries levelBounds, bool IsPlayer = true);
	virtual ~CharacterComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override{}
	void SetTransform(float, float, float) override {};

	void MoveRight(float amount);
	void MoveUp(float amount);

	void ResetBounds(Boundaries levelBounds);
	Direction GetPreviousDirection() const { return previous; }
	void SetPreviousDirection(Direction direction) { previous = direction; }
	Direction GetCurrentDirection() const { return current; }
	void SetCurrentDirection(Direction direction) { current = direction; }
	
	void SetGridSize(int size) { m_GridSize = size; }
	int GetGridSize() const { return m_GridSize; }
	bool GetIsPlayer() const { return m_IsPlayer; }
	void SetIsPlayerDigging(bool isDigging) { m_IsDigging = isDigging; }
	bool GetIsMovingAutomatic() const { return m_IsMoveAutomatic; }
	void SetIsMovingAutomatic(bool isMovingAuto) { m_IsMoveAutomatic = isMovingAuto; }

private:
	std::shared_ptr<dae::GameObject>& m_pCharacter;
	bool m_CanMove = true;
	bool m_IsDigging = false;
	Boundaries m_Boundaries;
	std::bitset<8> m_Sprite;
	Direction previous = Direction::none, current = Direction::right;
	void ResetBitSet();
	int m_GridSize = 1;
	bool m_IsPlayer;
	bool m_IsMoveAutomatic = false;
};

