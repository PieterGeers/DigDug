#include "MiniginPCH.h"
#include "SoundManager.h"


void SoundManager::Init(std::string&& data)
{
	mDataPath = std::move(data);
}

void SoundManager::LoadSoundEffect(const std::string& name, const std::string& path)
{
	const auto find = m_EffectMap.find(std::move(name));
	if (find != m_EffectMap.end())
		return;

	std::string fullPath{ mDataPath + path };
	std::shared_ptr<SoundEffect> temp = std::make_shared<SoundEffect>(std::move(fullPath));
	m_EffectMap.insert({ std::move(name), temp });
}

void SoundManager::LoadSoundStream(const std::string& name, const std::string& path)
{
	const auto find = m_StreamMap.find(std::move(name));
	if (find != m_StreamMap.end())
		return;

	std::string fullPath{ mDataPath + path };
	std::shared_ptr<SoundStream> temp = std::make_shared<SoundStream>(std::move(fullPath));
	m_StreamMap.insert({ std::move(name), temp });

}

void SoundManager::PlaySoundEffect(const std::string& name, int loops)
{
	const auto find = m_EffectMap.find(std::move(name));
	if (find != m_EffectMap.end())
		if (!(*find).second->Play(loops))
		{
			//error;
		}
	//error
}

void SoundManager::PlaySoundStream(const std::string& name, bool repeat)
{
	const auto find = m_StreamMap.find(std::move(name));
	if (find != m_StreamMap.end())
		if (!(*find).second->Play(repeat))
		{
			//error;
		}
	//error
}

void SoundManager::StopSoundEffect()
{
	Mix_HaltChannel(-1);
}

void SoundManager::StopSoundStream()
{
	Mix_HaltMusic();
}

void SoundManager::HaltSoundEffect()
{
	Mix_Pause(-1);
}

void SoundManager::HaltSoundStream()
{
	Mix_PauseMusic();
}

void SoundManager::ResumeSoundEffect()
{
	Mix_Resume(-1);
}

void SoundManager::ResumeSoundStream()
{
	Mix_ResumeMusic();
}
