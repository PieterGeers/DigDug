#include "MiniginPCH.h"
#include "SoundStream.h"
#include "Debug.h"

SoundStream::SoundStream(const std::string& path)
	:m_pMixMusic{ Mix_LoadMUS(path.c_str()) }
{
	if (m_pMixMusic == nullptr)
	{
		const std::string error = "SoundStream: Failed to load " + path + ": " + Mix_GetError();
		throw std::runtime_error(error);
	}
	m_IsLoaded = true;
}

SoundStream::~SoundStream()
{
	Mix_FreeMusic(m_pMixMusic);
	m_pMixMusic = nullptr;
}

bool SoundStream::IsLoaded() const
{
	return m_IsLoaded;
}

void SoundStream::Play(bool repeat) const
{
	if (!m_IsLoaded)
		Debug::LogWarning("SoundStream not loaded when trying to play");
	Mix_PlayMusic(m_pMixMusic, repeat ? -1 : 1);
}