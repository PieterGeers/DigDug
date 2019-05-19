#pragma once
#include "GameScene.h"
#include "ButtonManager.h"
#include "TextureRenderComponent.h"

class OptionsScreen final : public GameScene
{
public:
	OptionsScreen();
	~OptionsScreen() = default;

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	static void UpdateSoundEffectVolume(int value);
	static void UpdateSoundStreamVolume(int value);

private:
	std::shared_ptr<ButtonManager> m_ButtonManager;
	std::vector<std::shared_ptr<TextureRenderComponent>> m_StreamBars;
	std::vector<std::shared_ptr<TextureRenderComponent>> m_EffectBars;
	static int m_CurrentEffectVolume;
	static int m_CurrentStreamVolume;
};

