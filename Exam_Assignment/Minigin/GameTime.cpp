#include "MiniginPCH.h"
#include "GameTime.h"


void dae::GameTime::SetFixedElapsed(float fixedT)
{
	m_FixedElapsed = fixedT;
}

void dae::GameTime::SetDeltaT(float deltaT)
{
	m_TotalRunTime += deltaT;
	m_Elapsed = deltaT;
}

float dae::GameTime::DeltaT() const
{
	return m_Elapsed;
}

float dae::GameTime::FixedT() const
{
	return m_FixedElapsed;
}


