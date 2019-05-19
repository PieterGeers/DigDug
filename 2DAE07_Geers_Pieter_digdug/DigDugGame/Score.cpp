#include "pch.h"
#include "Score.h"
#include "ResourceManager.h"

void Score::Initialize()
{
	m_Score = 0;
	auto score = dae::ResourceManager::GetInstance().LoadFont("PressStart2P.ttf", 16);
	m_ScoreText = std::make_shared<TextRenderComponent>("Score 0", score, SDL_Color{ 214,0,24,255 });
	m_ScoreText->SetTransform(170, 0, 0);
}

void Score::AddScore(int score)
{
	m_Score += score;
	m_ScoreText->SetText("Score " + std::to_string(m_Score));
	m_ScoreText->Update();
}

void Score::Render() const
{
	m_ScoreText->Render();
}
