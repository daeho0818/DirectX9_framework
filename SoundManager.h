#pragma once
#include "Singleton.h"
#include "Sound.h"
#include <SDKsound.h>
class SoundManager : public Singleton<SoundManager>
{
	friend class LoadingManager;
public:
	SoundManager();
	~SoundManager();
	void Play(string key);
	void Stop(string key);
	void StopAll();

	void Update();

private:
	CSoundManager m_manager;
	map<string, LPDIRECTSOUNDBUFFER> m_channels;
	map<string, Sound*> m_sounds;

};
#define SOUND SoundManager::Instance()