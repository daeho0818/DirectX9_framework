#pragma once
class Scene_Title : public Scene
{
public:
	Scene_Title();
	~Scene_Title();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	Image* i_background = nullptr;
	Image* i_moon = nullptr;
	Image* i_cloud = nullptr;
	Image* i_mountain = nullptr;

	Image* i_logo = nullptr;

	Button* start_button = nullptr;
	Button* close_button = nullptr;

	Vector2 moon_position;
	Vector2 cloud_position[2];
	Vector2 mountain_position[2];

	float moon_sin_value = 0;
};

