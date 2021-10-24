#include "DXUT.h"
#include "SoundManager.h"

#include "LoadingManager.h"

SoundManager::SoundManager()
{
	m_manager.Initialize(DXUTGetHWND(), 0);
}

SoundManager::~SoundManager()
{
}

void SoundManager::Play(string key)
{
	LPDIRECTSOUNDBUFFER sb;
	Sound* sound = m_sounds.find(key)->second;

	var directSound = m_manager.GetDirectSound();
	directSound->DuplicateSoundBuffer(sound->m_cSound->GetBuffer(0), &sb);

	sb->SetVolume(sound->m_volume);
	sb->Play(0, 0, sound->m_cSound ? DSBSTATUS_LOOPING : 0);

	m_channels.insert(make_pair(key, sb));
}

void SoundManager::Stop(string key)
{
	var find = m_channels.find(key);
	if (find != m_channels.end())
	{
		find->second->Release();
		find = m_channels.erase(find);
	}
}

void SoundManager::StopAll()
{
	for (var iter : m_channels)
	{
		iter.second->Release();
	}
	m_channels.clear();
}

void SoundManager::Update()
{
	DWORD status;
	for (var iter = m_channels.begin(); iter != m_channels.end(); ++iter)
	{
		(*iter).second->GetStatus(&status);
		if (!(status & DSBSTATUS_PLAYING))
		{
			(*iter).second->Release();
			iter = m_channels.erase(iter);
		}
	}
}
