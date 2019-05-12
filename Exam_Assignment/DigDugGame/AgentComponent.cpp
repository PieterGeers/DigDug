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
#include "QuadCollisionComponent.h"
#include "DigDugRockComp.h"

int AgentComponent::m_Count = 0;
AgentComponent::AgentComponent(int maxInflate, int gridSize, int nbOfColumns)
	:m_MaxInflateBeforeBoom(maxInflate)
	,m_GridSize(gridSize)
	,m_NumberOfColumns(nbOfColumns)
{}

AgentComponent::~AgentComponent()
{
	if (m_StateMachine != nullptr)
		delete m_StateMachine;
}

void AgentComponent::Update()
{
	if (!m_Initialized)
		return;
	if (m_IsIdle)
	{
		if (m_InitialIdleTime > 0.0f)
			m_InitialIdleTime -= dae::GameTime::GetInstance().DeltaT();
		else if (CalculateClosestPlayerDistance() < 100.0f)
			m_IsIdle = false;
	}
	if (m_IsActive)
		m_StateMachine->Update();
	else if (!m_IsActive && m_StateMachine != nullptr)
	{
		delete m_StateMachine;
		m_StateMachine = nullptr;
		auto& agents = ServiceLocator::GetAgents();
		auto it = agents.find(m_ThisInstance);
		agents.erase(it);
		GetGameObject()->GetComponent<TextureRenderComponent>()->StopRender();
	}
}

void AgentComponent::Initialize()
{
	SMState* runState = new SMState{};
	SMState* changeToInvis = new SMState{};
	SMState* changeToNormal = new SMState{};
	SMState* inflate = new SMState{};
	SMState* dead = new SMState{};
	SMState* hitByRock = new SMState{};
	SMState* idle = new SMState{};

	idle->SetTransition(new SMTransition({ new StopBeingIdle() }, runState));

	changeToInvis->SetAction(new ChangeAnimation("Invisible"));
	changeToInvis->SetTransition(new SMTransition({ new AnimationChanged() }, runState));

	changeToNormal->SetAction(new ChangeAnimation("Walk"));
	changeToNormal->SetTransition(new SMTransition({ new AnimationChanged() }, runState));

	inflate->SetAction(new InflateAction());
	inflate->SetTransition(new SMTransition({ new StopBeingInflated() }, changeToNormal));
	inflate->SetTransition(new SMTransition({ new IsDead() }, dead));

	dead->SetEntryAction(new ChangeAnimation("Explode"));
	dead->SetAction(new DeadAction());

	hitByRock->SetEntryAction(new ChangeAnimation("Flat"));
	hitByRock->SetAction(new DeadAction());
	
	runState->SetAction(new WalkAction());
	runState->SetEntryAction(new FindNextPathAction());
	runState->SetTransition(new SMTransition({ new HasReachedNextPosition() }, runState));
	runState->SetTransition(new SMTransition({ new StartGoingInvisible() }, changeToInvis));
	runState->SetTransition(new SMTransition({ new StopGoingInvisible() }, changeToNormal));
	runState->SetTransition(new SMTransition({ new StartBeingInflated() }, inflate));
	runState->SetTransition(new SMTransition({new IsHitByRock()}, hitByRock));
	m_StateMachine =  new StateMachine(std::vector<SMState*>{runState, changeToInvis, changeToNormal, inflate, dead, hitByRock, idle}, idle, m_Count);
	m_ThisInstance = m_Count;
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

float AgentComponent::CalculateClosestPlayerDistance() const
{
	auto& players = ServiceLocator::GetPlayers();
	float closestDistance = -1.0f;
	for (const auto p : players)
	{
		const int distance = MVector2_INT{ static_cast<int>(p.second->GetTransform()->GetPosition().x), static_cast<int>(p.second->GetTransform()->GetPosition().y) }.DistanceSQR({ static_cast<int>(GetTransform()->GetPosition().x), static_cast<int>(GetTransform()->GetPosition().y) });
		if (closestDistance < 0.0f)
			closestDistance = sqrt(float(distance));
		else if (distance < int(closestDistance * closestDistance))
			closestDistance = sqrt(float(distance));
	}
	return closestDistance;
}

void AgentComponent::Collision()
{
	if (!m_IsInvisible)
	{
		auto collision = GetGameObject()->GetComponent<QuadCollisionComponent>();
		auto tags = collision->GetColliderTags();
		for (auto t : tags)
		{
			if (Debug::CompareStringLeft(t, "Attack", 6))
			{
				if (m_Collision == false)
				{
					m_Collision = true;
					m_IsBeingInflated = true;
					m_CurrentDeflateTime = m_DeflateTime;
					++m_InflateStatus;
					m_HasInflationChanged = true;
					return;
				}
				return;
			}
		}
		m_Collision = false;
	}
}

void AgentComponent::RockCollision()
{
	if (!m_IsInvisible)
	{
		auto collision = GetGameObject()->GetComponent<QuadCollisionComponent>();
		auto tags = collision->GetColliderTags();
		for (auto t : tags)
		{

			if (Debug::CompareStringLeft(t, "Rock", 4))
			{
				auto objs = collision->GetCollisionObjects().find(t);
				if (!m_IsHitByFallingRock && (*objs).second->GetGameObject()->GetComponent<DigDugRockComp>()->IsFalling())
				{
					m_IsHitByFallingRock = true;
					m_IsDead = true;
					return;
				}
			}
			else
				return;
		}
	}
}

void AgentComponent::Inflate()
{
	if (m_InflateStatus > 0)
	{
		m_CurrentDeflateTime -= dae::GameTime::GetInstance().DeltaT();
		if (m_CurrentDeflateTime <= 0.0f)
		{
			--m_InflateStatus;
			if (m_InflateStatus > 0)
			{
				m_CurrentDeflateTime = m_DeflateTime;
				m_HasInflationChanged = true;
			}
			else
				m_IsBeingInflated = false;
		}
	}
	if (m_InflateStatus == m_MaxInflateBeforeBoom)
		m_IsDead = true;
	if (m_IsDead == false && m_HasInflationChanged)
	{
		GetGameObject()->GetComponent<Animator>()->SetActiveAnimation("Stage" + std::to_string(m_InflateStatus));
		m_HasInflationChanged = false;
	}
}

void AgentComponent::Dead()
{
	if (m_IsDead)
	{
		m_DeadTime -= dae::GameTime::GetInstance().DeltaT();
		if (m_DeadTime <= 0.0f)
		{
			std::string tag = GetGameObject()->GetComponent<QuadCollisionComponent>()->GetTag();
			auto it = QuadCollisionComponent::GetCollisionObjects().find(tag);
			QuadCollisionComponent::GetCollisionObjects().erase(it);
			m_IsActive = false;
		}
	}
}

void AgentComponent::FixedUpdate()
{
	int idx = CalculateGridIndex();
	auto& grid = LevelComponent::GetGrid();
	if (!m_IsInvisible && std::static_pointer_cast<DigDugCell>(grid[idx])->hasVisited == false)
		m_IsInvisible = true;
	else if (m_IsInvisible && std::static_pointer_cast<DigDugCell>(grid[idx])->hasVisited)
		m_IsInvisible = false;
	Collision();
	RockCollision();
}
