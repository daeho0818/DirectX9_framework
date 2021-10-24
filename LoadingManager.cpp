#include "DXUT.h"
#include "LoadingManager.h"

#include "SoundManager.h"

LoadingManager::LoadingManager()
{
	(*SOUND->m_manager).Initialize(DXUTGetHWND(), 1);
}

LoadingManager::~LoadingManager()
{
}

void LoadingManager::AddImage(string key, string path, int count)
{
	ImgsInfo imgInfo = { key, path, count };
	imgsInfo.push_back(imgInfo);
}

void LoadingManager::AddSound(string key, wstring path, LONG volume, bool loop)
{
	SoundsInfo soundInfo = { key, path, volume, loop };
	soundsInfo.push_back(soundInfo);
}

void LoadingManager::Loading()
{
	while (!imgsInfo.empty())
	{
		for (auto iter : imgsInfo)
			ImageLoad(iter);
	}
	while (!soundsInfo.empty())
	{
		for (auto iter : soundsInfo)
			SoundLoad(iter);
	}
}

void LoadingManager::ImageLoad(ImgsInfo imgInfo)
{
	auto find = m_images.find(imgInfo.key);

	if (find == m_images.end())
	{
		char path[256] = "";
		sprintf(path, "./Resources/Images/%s.png", imgInfo.path.c_str());

		LPDIRECT3DTEXTURE9 ptr;
		D3DXIMAGE_INFO info;

		if (imgInfo.count == 0)
		{
			if (D3DXCreateTextureFromFileExA(DEVICE, path, -2, -2, 0, 0,
				D3DFMT_UNKNOWN, D3DPOOL_MANAGED, -1, -1, 0, &info, nullptr, &ptr) == S_OK)
			{
				Image* image = new Image(ptr, info);
				m_images.insert(make_pair(imgInfo.key, image));
			}
		}
		else
		{
			char key[128] = "";

			for (int i = 0; i < imgInfo.count; i++)
			{
				sprintf(key, "%s%d", imgInfo.key.c_str(), i);
				sprintf(path, "./Resources/Image/%s (%d).png", imgInfo.key.c_str(), i);

				if (D3DXCreateTextureFromFileExA(DEVICE, path, -2, -2, 0, 0,
					D3DFMT_UNKNOWN, D3DPOOL_MANAGED, -1, -1, 0, &info, nullptr, &ptr) == S_OK)
				{
					Image* image = new Image(ptr, info);
					m_images.insert(make_pair((string)key, image));
				}
			}
		}
	}
}

void LoadingManager::SoundLoad(SoundsInfo soundInfo)
{
	wchar_t path[256] = L"";
	CSound* cSound;
	swprintf(path, L"./Resources/Sounds/%s.wav", soundInfo.path.c_str());
	SOUND->m_manager.Create(&cSound, path, DSBCAPS_CTRLVOLUME);
	Sound* sound = new Sound(soundInfo.volume, soundInfo.loop, cSound);
	SOUND->m_sounds.insert(make_pair(soundInfo.key, sound));
}
