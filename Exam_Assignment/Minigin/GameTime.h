#pragma once
#include "Singleton.h"

namespace dae
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		GameTime() = default;
		~GameTime() = default;

		GameTime(const GameTime& other) = delete;
		GameTime(GameTime&& other) = delete;
		GameTime& operator=(const GameTime& other) = delete;
		GameTime& operator=(GameTime&& other) = delete;

		void SetFixedElapsed(float fixedT);
		void SetDeltaT(float deltaT);
		float DeltaT() const;
		float FixedT() const;
	private:
		float m_TotalRunTime = 0.0f;
		float m_FixedElapsed = 0.0f;
		float m_Elapsed = 0.0f;
	};
}
