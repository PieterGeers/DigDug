#pragma once
class SoundStream
{
public:
	SoundStream(const std::string& path);
	~SoundStream();

	bool IsLoaded() const;
	bool Play(bool repeat) const;

private:
	Mix_Music *m_pMixMusic;
	bool m_IsLoaded = false;
};

