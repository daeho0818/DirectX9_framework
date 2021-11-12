#pragma once
#include "Singleton.h"
class ImageManager : public Singleton<ImageManager>
{
private:
	struct ImageInfo
	{
		ImageInfo() {}
		ImageInfo(string key, string path, int count)
		{
			this->key = key;
			this->path = path;
			this->count = count;
		}
		string key;
		string path;
		int count;
	};

public:
	ImageManager();
	~ImageManager();

	void AddImage(string _key, string _path, int count = 0);
	void QuickLoad(string _key, string _path, int count = 0);
	Image* FindImage(string _key);
	vector<Image*> MakeAnimation(string _key);
	void Loading();

private:
	void ImageLoad(ImageInfo imageInfo);

	map<string, Image*> m_images;
	vector<ImageInfo> image_informations;

	int all_image_count;
};
#define IMAGE ImageManager::Instance()