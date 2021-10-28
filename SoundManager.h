#pragma once
#include "Singleton.h"
#include "Sound.h"
#include <SDKsound.h>
class SoundManager : public Singleton<SoundManager>
{
private:
	struct SoundInfo
	{
		SoundInfo() {}
		SoundInfo(string key, wstring path, LONG volume, bool loop)
		{
			this->key = key;
			this->path = path;
			this->volume = volume;
			this->loop = loop;
		}
		string key;
		wstring path;
		LONG volume;
		bool loop;
	};

public:
	SoundManager();
	~SoundManager();

	void AddSound(string key, wstring path, LONG volume, bool loop);

	void Play(string key);
	void Stop(string key);
	void StopAll();

	void Update();

	void Loading();

private:
	CSoundManager m_manager;
	map<string, LPDIRECTSOUNDBUFFER> m_channels;
	map<string, Sound*> m_sounds;

	vector<SoundInfo> sound_informations;

	void SoundLoad(SoundInfo soundInfo);
};
#define SOUND SoundManager::Instance()