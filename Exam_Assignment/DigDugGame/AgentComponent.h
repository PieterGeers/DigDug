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

	void FixedUpdate() override;
	void Render() override{}
	void SetTransform(float , float , float ) override{}

	static int GetCount() { return m_Count; }

	//Variables
	bool m_IsInvisible = false;
	bool m_WasInvisible = false;
	bool m_HasReachedEndPosition = false;
	bool m_IsBeingInflated = false;
	bool m_HasAnimationChanged = false;

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
};