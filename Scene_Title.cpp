#include "DXUT.h"
#include "Scene_Title.h"

Scene_Title::Scene_Title()
{
}

Scene_Title::~Scene_Title()
{
}

void Scene_Title::Init()
{
	i_background = IMAGE->FindImage("Title_BG");
	i_moon = IMAGE->FindImage("Title_Moon");
	i_cloud = IMAGE->FindImage("Title_Cloud");
	i_mountain = IMAGE->FindImage("Title_Mountain");

	moon_position = Vector2(300, 200);

	cloud_position[0] = Vector2(WINSIZEX / 2, i_cloud->info.Height / 2);
	cloud_position[1] = cloud_position[0] + Vector2(WINSIZEX, 0);

	mountain_position[0] = Vector2(WINSIZEX / 2, WINSIZEY - i_mountain->info.Height / 2);
	mountain_position[1] = mountain_position[0] + Vector2(WINSIZEX, 0);
}

void Scene_Title::Update()
{
	moon_sin_value += DELTA * 50;

	moon_position = Vector2(moon_position.x, 200 + sin(D3DXToRadian(moon_sin_value)) * 30);

	cloud_position[0].x -= 10;
	cloud_position[1].x -= 10;

	mountain_position[0].x -= 2;
	mountain_position[1].x -= 2;

	for (int i = 0; i < 2; i++)
	{
		if (cloud_position[i].x <= -WINSIZEX / 2)
			cloud_position[i].x = WINSIZEX + WINSIZEX / 2;

		if (mountain_position[i].x <= -WINSIZEX / 2)
			mountain_position[i].x = WINSIZEX + WINSIZEX / 2;
	}

	if (GetKeyDown(VK_RETURN))
		SCENE->ChangeScene("Scene_Stage2");
}

void Scene_Title::Render()
{
	RENDER->CenterRender(i_background, CENTER);

	RENDER->CenterRender(i_mountain, mountain_position[0]);
	RENDER->CenterRender(i_mountain, mountain_position[1]);

	RENDER->CenterRender(i_moon, moon_position);

	RENDER->CenterRender(i_cloud, cloud_position[0]);
	RENDER->CenterRender(i_cloud, cloud_position[1]);
}

void Scene_Title::UIRender()
{
}
void Scene_Title::Release()
{
}
