#pragma once
#include "Singleton.h"
class ImageManager : public Singleton<ImageManager>
{
public:
	ImageManager();
	~ImageManager();

	void QuickLoad(string _key, string _path, int count = 0);
	Image* FindImage(string _key);
	vector<Image*> MakeAnimation(string _key);

private:
	map<string, Image*> m_images;

	int all_image_count;
};
#define IMAGE ImageManager::Instance()