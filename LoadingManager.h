#pragma once
#include "Singleton.h"
#include "Image.h"
#include "Sound.h"

class LoadingManager : public Singleton<LoadingManager>
{
	friend class SoundManager;
	friend class ImageC;

public:
	LoadingManager();
	~LoadingManager();

	void AddImage(string key, string path, int count = 1);
	void AddSound(string key, wstring path, LONG volume, bool loop);

	void Loading();

private:
	struct ImgsInfo
	{
		string key;
		string path;
		int count;
	};
	list<ImgsInfo> imgsInfo;

	struct SoundsInfo
	{
		string key;
		wstring path;
		LONG volume;
		bool loop;
	};
	list<SoundsInfo> soundsInfo;

	map<string, Image*> m_images;

	void ImageLoad(ImgsInfo imgInfo);
	void SoundLoad(SoundsInfo soundInfo);
};
#define LOADING LoadingManager::Instance()