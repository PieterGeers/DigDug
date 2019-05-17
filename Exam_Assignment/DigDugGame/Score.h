#pragma once
#include "TextRenderComponent.h"
#include "Singleton.h"

class Score final:public dae::Singleton<Score>
{
public:
	Score() = default;
	~Score() = default;

	void Initialize();
	void AddScore(int score);
	void Render() const;

	int GetScore() const { return static_cast<int>(m_Score); }

private:
	unsigned m_Score;
	std::shared_ptr<TextRenderComponent> m_ScoreText;
};

