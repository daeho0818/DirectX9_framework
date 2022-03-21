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
	// 타이틀 화면 리소스
	IMAGE->QuickLoad("Title_BG", "Scene/Title/Title_BG");
	IMAGE->QuickLoad("Title_Moon", "Scene/Title/Title_Moon");
	IMAGE->QuickLoad("Title_Cloud", "Scene/Title/Title_Cloud");
	IMAGE->QuickLoad("Title_Mountain", "Scene/Title/Title_Mountain");
	IMAGE->QuickLoad("Title_Logo", "Scene/Title/Title_Logo");
	IMAGE->QuickLoad("Title_Start", "Scene/Title/Title_Start");
	IMAGE->QuickLoad("Title_Close", "Scene/Title/Title_Close");

	// 플레이어 / 적 캐릭터
	AddImage("Player", "Object/Player/Player");
	AddImage("Enemy1", "Object/Enemy/Enemies/Enemy_1");
	AddImage("Enemy2", "Object/Enemy/Enemies/Enemy_2");
	AddImage("Enemy3", "Object/Enemy/Enemies/Enemy_3");
	AddImage("Boss1_1", "Object/Enemy/Boss/Stage1/Boss_1");

	AddImage("Boss2_1", "Object/Enemy/Boss/Stage2/Boss_1");
	AddImage("Boss2_1_LTop", "Object/Enemy/Boss/Stage2/Cannon_LTop");
	AddImage("Boss2_1_RTop", "Object/Enemy/Boss/Stage2/Cannon_RTop");
	AddImage("Boss2_1_LBottom", "Object/Enemy/Boss/Stage2/Cannon_LBottom");
	AddImage("Boss2_1_RBottom", "Object/Enemy/Boss/Stage2/Cannon_RBottom");

	// 총알
	AddImage("Bullet_Player", "Object/Bullet/Bullet_Player");
	AddImage("Bullet_Enemy_1", "Object/Bullet/Bullet_Enemy_1");
	AddImage("Bullet_Enemy_2", "Object/Bullet/Bullet_Enemy_2");
	AddImage("Bullet_Enemy_3", "Object/Bullet/Bullet_Enemy_3");

	// 인게임
	AddImage("Background_1", "Scene/Ingame/Stage_1/Background_1");
	AddImage("Background_2", "Scene/Ingame/Stage_2/Background_2");
	AddImage("Player_Hp_Bg", "Scene/Ingame/Player_Hp_BG");
	AddImage("Player_Hp_Bar", "Scene/Ingame/Player_Hp_Bar");

	// 폭발 애니메이션
	AddImage("Explosion", "Effect/Explosion/Explosion", 13);

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

	if (!image_informations.empty())
	{
		ImageInfo image_info = image_informations.back();
		image_informations.pop_back();
		IMAGE->QuickLoad(image_info.key, image_info.path, image_info.count);
	}
	else
		SCENE->ChangeScene("Scene_Title");
}

void Scene_Loading::Render()
{

	RENDER->CenterRender(i_background, CENTER);

	RENDER->CenterRender(i_moon, moon_position);

	RENDER->CenterRender(i_mountain, mountain_position[0]);
	RENDER->CenterRender(i_mountain, mountain_position[1]);

	RENDER->CenterRender(i_cloud, cloud_position[0]);
	RENDER->CenterRender(i_cloud, cloud_position[1]);
}

void Scene_Loading::UIRender()
{
}

void Scene_Loading::Release()
{
	image_informations.clear();
}


void Scene_Loading::AddImage(string key, string path, int count)
{
	image_informations.push_back(ImageInfo(key, path, count));
}