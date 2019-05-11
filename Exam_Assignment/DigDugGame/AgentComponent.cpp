#include "pch.h"
#include "AgentComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Animator.h"
#include "ServiceLocator.h"
#include "SMState.h"
#include "SMTransition.h"
#include "LevelComponent.h"
#include "DigDugStructs.h"
#include "Actions.h"
#include "Conditions.h"

int AgentComponent::m_Count = 0;
AgentComponent::AgentComponent(int maxInflate, int gridSize, int nbOfColumns)
	:m_MaxInflateBeforeBoom(maxInflate)
	,m_GridSize(gridSize)
	,m_NumberOfColumns(nbOfColumns)
{}

AgentComponent::~AgentComponent()
{
	delete m_StateMachine;
}

void AgentComponent::Update()
{
	if (!m_Initialized)
		return;
	m_StateMachine->Update();
}

void AgentComponent::Initialize()
{
	SMState* runState = new SMState{};
	SMState* changeToInvis = new SMState{};
	SMState* changeToNormal = new SMState{};

	changeToInvis->SetAction(new ChangeAnimation("Invisible"));
	changeToInvis->SetTransition(new SMTransition({ new AnimationChanged() }, runState));

	changeToNormal->SetAction(new ChangeAnimation("Walk"));
	changeToNormal->SetTransition(new SMTransition({ new AnimationChanged() }, runState));

	runState->SetAction(new WalkAction());
	runState->SetEntryAction(new FindNextPathAction());
	runState->SetTransition(new SMTransition({ new HasReachedNextPosition() }, runState));
	runState->SetTransition(new SMTransition({ new StartGoingInvisible() }, changeToInvis));
	runState->SetTransition(new SMTransition({ new StopGoingInvisible() }, changeToNormal));
	m_StateMachine =  new StateMachine(std::vector<SMState*>{runState, changeToInvis, changeToNormal}, runState, m_Count);
	++m_Count;
	m_Initialized = true;
}

void AgentComponent::SmoothWalkTo(MVector2_INT pos)
{
	if (m_HasReachedEndPosition == false)
	{
		m_ElapsedTime += dae::GameTime::GetInstance().DeltaT();
		if (m_ElapsedTime >= dae::GameTime::GetInstance().FixedT())
		{
			m_ElapsedTime -= dae::GameTime::GetInstance().FixedT();
			if (GetTransform()->GetPosition().x != pos.x)
			{
				if (GetTransform()->GetPosition().x < pos.x)
					GetGameObject()->Translate(2, 0, 0);
				else
					GetGameObject()->Translate(-2, 0, 0);
			}
			else if (GetTransform()->GetPosition().y != pos.y)
			{
				if (GetTransform()->GetPosition().y < pos.y)
					GetGameObject()->Translate(0, 2, 0);
				else
					GetGameObject()->Translate(0, -2, 0);
			}
			else if (m_PositionInPath < m_CurrentPath.size()-1)
			{
				++m_PositionInPath;
				m_NextPosition = m_CurrentPath[m_PositionInPath];
			}
			else
			{
				m_HasReachedEndPosition = true;
				m_PositionInPath = 0;
				m_CurrentPath = {};
			}
		}
	}
}

void AgentComponent::SetAnimation(const std::string& anim)
{
	GetGameObject()->GetComponent<Animator>()->SetActiveAnimation(std::move(anim));
	m_HasAnimationChanged = true;
}

int AgentComponent::CalculateGridIndex() const
{
	const int x = static_cast<const int>(GetTransform()->GetPosition().x) / m_GridSize;
	const int y = static_cast<const int>(GetTransform()->GetPosition().y) / m_GridSize;
	return y * m_NumberOfColumns + x;
}

int AgentComponent::CalculateClosestPlayerIndex() const
{
	auto& players = ServiceLocator::GetPlayers();
	int closestIdx = -1;
	int closestDistance = -1;
	for (const auto p : players)
	{
		if (closestIdx == -1)
			closestIdx = p.first;
		MVector2_INT pPos{ static_cast<int>(p.second->GetTransform()->GetPosition().x), static_cast<int>(p.second->GetTransform()->GetPosition().y) };
		const int distance = pPos.DistanceSQR({ static_cast<int>(GetTransform()->GetPosition().x), static_cast<int>(GetTransform()->GetPosition().y) });
		if (closestDistance == -1)
			closestDistance = distance;
		else if (distance < closestDistance)
		{
			closestDistance = distance;
			closestIdx = p.first;
		}
	}
	if (closestIdx != -1)
	{
		const int x = static_cast<int>(players[closestIdx]->GetTransform()->GetPosition().x) / m_GridSize;
		const int y = static_cast<int>(players[closestIdx]->GetTransform()->GetPosition().y) / m_GridSize;
		return y * m_NumberOfColumns + x;
	}
	return -1;
}

void AgentComponent::FixedUpdate()
{
	int idx = CalculateGridIndex();
	auto& grid = LevelComponent::GetGrid();
	if (!m_IsInvisible && std::static_pointer_cast<DigDugCell>(grid[idx])->hasVisited == false)
		m_IsInvisible = true;
	else if (m_IsInvisible && std::static_pointer_cast<DigDugCell>(grid[idx])->hasVisited)
		m_IsInvisible = false;
}
