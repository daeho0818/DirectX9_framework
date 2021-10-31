#include "DXUT.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::AddSound(string key, wstring path, LONG volume, bool loop)
{
	sound_informations.push_back(SoundInfo(key, path, volume, loop));
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
		SAFE_DELETE(iter.second);
	}
	m_channels.clear();
}

void SoundManager::Init()
{
	m_manager.Initialize(DXUTGetHWND(), 0);
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

void SoundManager::Loading()
{
	all_sound_count = sound_informations.size();

	while (!sound_informations.empty())
	{
		SoundLoad(sound_informations.back());
		sound_informations.pop_back();
	}

	// 로딩 끝난 후 실행할 내용
}

void SoundManager::SoundLoad(SoundInfo soundInfo)
{
	wchar_t path[256] = L"";
	CSound* cSound;
	swprintf(path, L"./Resources/Sounds/%s.wav", soundInfo.path.c_str());
	m_manager.Create(&cSound, path, DSBCAPS_CTRLVOLUME);
	Sound* sound = new Sound(soundInfo.volume, soundInfo.loop, cSound);
	m_sounds.insert(make_pair(soundInfo.key, sound));
}
