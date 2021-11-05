#include "DXUT.h"
#include "ImageManager.h"

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
	for (var iter : m_images)
	{
		iter.second->ptr->Release();
		SAFE_DELETE(iter.second);
	}
	m_images.clear();
	image_informations.clear();
}

void ImageManager::AddImage(string key, string path, int count)
{
	image_informations.push_back(ImageInfo(key, path, count));
}

void ImageManager::QuickLoad(string _key, string _path, int count)
{
	auto find = m_images.find(_key);

	if (find == m_images.end())
	{
		char key[256] = "";
		char path[256] = "";

		LPDIRECT3DTEXTURE9 ptr;
		D3DXIMAGE_INFO info;

		for (int i = 0; i <= count; i++)
		{
			if (count == 0)
			{
				sprintf(key, "%s", _key.c_str());
				sprintf(path, "./Resources/Images/%s.png", _path.c_str());
			}
			else
			{
				sprintf(key, "%s%d", _key.c_str(), i);
				sprintf(path, "./Resources/Images/%s (%d).png", _path.c_str(), i);
			}

			if (D3DXCreateTextureFromFileExA(DEVICE, path, -2, -2, 0, 0,
				D3DFMT_UNKNOWN, D3DPOOL_MANAGED, -1, -1, 0, &info, nullptr, &ptr) == S_OK)
			{
				Image* image = new Image(ptr, info);
				m_images.insert(make_pair((string)key, image));
			}
		}
	}
}

Image* ImageManager::FindImage(string key)
{
	var find = m_images.find(key);

	return find != m_images.end() ? find->second : nullptr;
}

void ImageManager::Loading()
{
	all_image_count = image_informations.size();

	while (!image_informations.empty())
	{
		ImageLoad(image_informations.back());
		image_informations.pop_back();
	}

	// 로딩 끝났을 때 실행할 내용
}

void ImageManager::ImageLoad(ImageInfo imageInfo)
{
	auto find = m_images.find(imageInfo.key);

	if (find == m_images.end())
	{
		char key[256] = "";
		char path[256] = "";

		LPDIRECT3DTEXTURE9 ptr;
		D3DXIMAGE_INFO info;

		for (int i = 0; i <= imageInfo.count; i++)
		{
			if (imageInfo.count == 0)
			{
				sprintf(key, "%s", imageInfo.key.c_str());
				sprintf(path, "./Resources/Images/%s.png", imageInfo.path.c_str());
			}
			else
			{
				sprintf(key, "%s%d", imageInfo.key.c_str(), i);
				sprintf(path, "./Resources/Images/%s (%d).png", imageInfo.path.c_str(), i);
			}

			if (D3DXCreateTextureFromFileExA(DEVICE, path, -2, -2, 0, 0,
				D3DFMT_UNKNOWN, D3DPOOL_MANAGED, -1, -1, 0, &info, nullptr, &ptr) == S_OK)
			{
				Image* image = new Image(ptr, info);
				m_images.insert(make_pair((string)key, image));
			}
		}
	}
}
