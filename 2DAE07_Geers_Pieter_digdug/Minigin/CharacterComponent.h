#pragma once
#include "BaseComponent.h"
#include "Structs.h"

class CharacterComponent : public BaseComponent	
{
public:
	CharacterComponent(Boundaries levelBounds);
	~CharacterComponent() = default;

	void Update() override;
	void FixedUpdate() override;
	void Render() override{}
	void SetTransform(float, float, float) override {};

	virtual void MoveRight(float amount);
	virtual void MoveUp(float amount);

	void ResetBounds(Boundaries levelBounds);
	Direction GetPreviousDirection() const { return previous; }
	void SetPreviousDirection(Direction direction) { previous = direction; }
	Direction GetCurrentDirection() const { return current; }
	void SetCurrentDirection(Direction direction) { current = direction; }
	
	void SetGridSize(int size) { m_GridSize = size; }
	int GetGridSize() const { return m_GridSize; }
	int GetPreviousLocation() const { return m_prevIdx; }
	void SetPreviousLocation(int idx) { m_prevIdx = idx; }

protected:
	Boundaries m_Boundaries;
	Direction previous = Direction::none, current = Direction::right;
	int m_GridSize = 1;
	int m_prevIdx = -1;
	
};

