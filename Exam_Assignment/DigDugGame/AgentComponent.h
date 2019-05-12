#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "StateMachine.h"
#include "ServiceLocator.h"

class AgentComponent : public BaseComponent
{
public:
	AgentComponent(int maxInflate, int gridSize, int nbOfColumns);
	AgentComponent() = default;
	~AgentComponent();

	void Update() override;

	void Initialize();

	void SmoothWalkTo(MVector2_INT pos);
	void SetAnimation(const std::string& anim);
	int CalculateGridIndex() const;
	int CalculateClosestPlayerIndex() const;
	float CalculateClosestPlayerDistance() const;

	void Collision();
	void RockCollision();
	void Inflate();
	void Dead();

	void FixedUpdate() override;
	void Render() override{}
	void SetTransform(float , float , float ) override{}

	static int GetCount() { return m_Count; }

	//Variables
	bool m_IsInvisible = false;
	bool m_WasInvisible = false;
	bool m_HasReachedEndPosition = false;
	bool m_IsBeingInflated = false;
	bool m_WasBeingInflated = false;
	bool m_HasAnimationChanged = false;
	bool m_IsHitByFallingRock = false;
	bool m_IsIdle = true;
	bool m_IsDead = false;

	int m_InflateStatus = 0;

	MVector2_INT m_NextPosition = { 0,0 };
	std::vector<MVector2_INT> m_CurrentPath{};

private:
	float m_ElapsedTime = 0.0f;
	int m_MaxInflateBeforeBoom = 0;
	int m_GridSize = 0;
	int m_NumberOfColumns = 0;
	StateMachine* m_StateMachine = nullptr;
	bool m_Initialized = false;
	static int m_Count;
	unsigned m_PositionInPath = 0;
	float m_DeflateTime = 0.5f;
	float m_CurrentDeflateTime = 0.0f;
	bool m_Collision = false;
	bool m_HasInflationChanged = false;
	float m_DeadTime = 1.0f;
	bool m_IsActive = true;
	int m_ThisInstance = 0;
	float m_InitialIdleTime = 1.0f;
};