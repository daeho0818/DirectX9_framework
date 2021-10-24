#include "DXUT.h"
#include "ImageC.h"

ImageC::ImageC()
{
}

ImageC::~ImageC()
{
}

Image* ImageC::GetImage(string key)
{
	var find = LOADING->m_images.find(key);
	if (find != LOADING->m_images.end()) return find->second;
	return nullptr;
}

vector<Image*> ImageC::GetAnimation(string key)
{
	map<string, Image*> images = LOADING->m_images;
	vector<Image*> animations;
	char Key[128] = "";
	for (int i = 0;; i++)
	{
		sprintf(Key, "%s%d", key.c_str(), i);
		var find = images.find(Key);
		if (find == images.end()) break;
		animations.push_back(find->second);
	}
	return animations;
}

void ImageC::Init()
{
}

void ImageC::Update()
{
}

void ImageC::Render()
{
}

void ImageC::Release()
{
}
