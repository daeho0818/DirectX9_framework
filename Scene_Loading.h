#pragma once
class Scene_Loading : public Scene
{
public:
	Scene_Loading();
	~Scene_Loading();

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	void AddImage(string _key, string _path, int count = 0);

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
	vector<ImageInfo> image_informations;


	Image* i_background = nullptr;
	Image* i_moon = nullptr;
	Image* i_cloud = nullptr;
	Image* i_mountain = nullptr;

	Vector2 moon_position;
	Vector2 cloud_position[2];
	Vector2 mountain_position[2];

	float moon_sin_value = 0;
};

