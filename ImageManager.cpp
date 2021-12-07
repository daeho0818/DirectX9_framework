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

Image* ImageManager::FindImage(string _key)
{
	var find = m_images.find(_key);

	return find != m_images.end() ? find->second : nullptr;
}

vector<Image*> ImageManager::MakeAnimation(string _key)
{
	vector<Image*> animation;

	char key[256] = "";

	for (int i = 0;; i++)
	{
		sprintf(key, "%s%d", _key.c_str(), i);
		var find = m_images.find(key);
		if (find == m_images.end())
			break;
		animation.push_back(find->second);
	}
	return animation;
}