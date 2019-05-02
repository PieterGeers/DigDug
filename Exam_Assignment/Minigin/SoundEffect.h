#pragma once
#pragma comment(lib, "SDL2_mixer.lib")  

class SoundEffect
{
public:
	SoundEffect(const std::string& path);
	~SoundEffect();

	bool IsLoaded() const;
	bool Play(int loops) const;
	void SetVolume(int value);
	int GetVolume() const;

private:
	Mix_Chunk* m_pMixChunk;
	bool m_IsLoaded = false;
};

