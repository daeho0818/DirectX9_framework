#include "DXUT.h"
#include "Scene_Loading.h"

Scene_Loading::Scene_Loading()
{
}

Scene_Loading::~Scene_Loading()
{
}

void Scene_Loading::Init()
{
	IMAGE->QuickLoad("Main_BG", "Scene/Title/Main_BG");
	IMAGE->QuickLoad("Main_BG_Moon", "Scene/Title/Main_BG_Moon");
	IMAGE->QuickLoad("Main_BG_Cloud", "Scene/Title/Main_BG_Cloud");
	IMAGE->QuickLoad("Main_BG_Mountains", "Scene/Title/Main_BG_Mountains");

	i_background = IMAGE->FindImage("Main_BG");
	i_moon = IMAGE->FindImage("Main_BG_Moon");
	i_cloud = IMAGE->FindImage("Main_BG_Cloud");
	i_mountain = IMAGE->FindImage("Main_BG_Mountains");

	// IMAGE->AddImage("", "");

	// IMAGE->Loading();

	moon_position = Vector2(300, 200);

	cloud_position[0] = Vector2(WINSIZEX / 2, i_cloud->info.Height / 2);
	cloud_position[1] = cloud_position[0] + Vector2(WINSIZEX, 0);

	mountain_position[0] = Vector2(WINSIZEX / 2, WINSIZEY - i_mountain->info.Height / 2);
	mountain_position[1] = mountain_position[0] + Vector2(WINSIZEX, 0);
}

float moon_sin_value = 0;
void Scene_Loading::Update()
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

	if (DXUTIsKeyDown(VK_RETURN))
	{
		SCENE->ChangeScene("Scene_TItle");
	}
}

void Scene_Loading::Render()
{
	RENDER->CenterRender(i_background, CENTER);
	RENDER->CenterRender(i_moon, moon_position);

	RENDER->CenterRender(i_cloud, cloud_position[0]);
	RENDER->CenterRender(i_cloud, cloud_position[1]);

	RENDER->CenterRender(i_mountain, mountain_position[0]);
	RENDER->CenterRender(i_mountain, mountain_position[1]);
}

void Scene_Loading::UIRender()
{
}

void Scene_Loading::Release()
{
}
