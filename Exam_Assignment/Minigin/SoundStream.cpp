#include "MiniginPCH.h"
#include "SoundStream.h"

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

bool SoundStream::Play(bool repeat) const
{
	if (!m_IsLoaded)
		return false;
	const int result{ Mix_PlayMusic(m_pMixMusic, repeat ? -1 : 1) };
	return result == 0 ? true : false;
}
