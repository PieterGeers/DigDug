#pragma once
#include "Singleton.h"
#include "SoundEffect.h"
#include "SoundStream.h"
#include <unordered_map>

class SoundManager final : public dae::Singleton<SoundManager>
{
	std::string mDataPath;
public:
	SoundManager() = default;

	void Init(std::string&& data);

	void LoadSoundEffect(const std::string& name, const std::string& path);
	void LoadSoundStream(const std::string& name, const std::string& path);

	void PlaySoundEffect(const std::string& name, int loops);
	void PlaySoundStream(const std::string& name, bool repeat);

	static void StopSoundEffect();
	static void StopSoundStream();

	static void HaltSoundEffect();
	static void HaltSoundStream();

	static void ResumeSoundEffect();
	static void ResumeSoundStream();

private:
	std::unordered_map<std::string, std::shared_ptr<SoundEffect>> m_EffectMap;
	std::unordered_map<std::string, std::shared_ptr<SoundStream>> m_StreamMap;

};

