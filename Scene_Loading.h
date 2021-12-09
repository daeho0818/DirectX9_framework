#pragma once
class Scene_Loading : public Scene
{
public:
	Scene_Loading();
	~Scene_Loading();

	// Scene을(를) 통해 상속됨
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


	Image* i_background = null;
	Image* i_moon = null;
	Image* i_cloud = null;
	Image* i_mountain = null;

	Vector2 moon_position;
	Vector2 cloud_position[2];
	Vector2 mountain_position[2];

	float moon_sin_value = 0;
};

