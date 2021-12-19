#include "DXUT.h"
#include "Scene_Stage1.h"

Scene_Stage1::Scene_Stage1()
{
}

Scene_Stage1::~Scene_Stage1()
{
}

void Scene_Stage1::Init()
{
	pattern_helper = new	PatternHelper();

	m_playerObject = OBJECT->CreateObject("Player", ObjType::EPlayer, CENTER);
	m_player = m_playerObject->AddComponent<Player>();

	pattern2 = false;

	pattern_helper->SetPattern(0, 3, 7, [&](float current_coolTime, bool is_end)->void
		{
			WavePattern1(current_coolTime, is_end);
		});
	pattern_helper->SetPattern(1, 3, 7, [&](float current_coolTime, bool is_end)->void
		{
			WavePattern2(current_coolTime, is_end);
		});
	pattern_helper->SetPattern(2, 3, 7, [&](float current_coolTime, bool is_end)->void
		{
			WavePattern3(current_coolTime, is_end);
		});
	pattern_helper->SetPattern(3
, 3, 7, [&](float current_coolTime, bool is_end)->void
		{
			WavePattern4(current_coolTime, is_end);
		});

	// m_bossObject = OBJECT->CreateObject("Boss", ObjType::EEnemy, Vector2(WINSIZEX / 2, -300));
	// m_boss = m_bossObject->AddComponent<Boss1_1>();

	enemy2_position[0] = Vector2(-50, 50);
	enemy2_position[1] = Vector2(WINSIZEX + 50, 50);
}

void Scene_Stage1::Update()
{
	srand(time(NULL));

	pattern_helper->Update();
}

void Scene_Stage1::Render()
{
}

void Scene_Stage1::UIRender()
{
}

void Scene_Stage1::Release()
{
	SAFE_DELETE(pattern_helper);
}

void Scene_Stage1::WavePattern1(float current_coolTime, bool is_end)
{
	if (is_end)
	{
		enemy1_position_x = WINSIZEX / 2 - 50;
		t_enemy1_spawn = null;
	}
	else if (t_enemy1_spawn == null)
	{
		enemy1_position_x = WINSIZEX / 2 - 300;

		t_enemy1_spawn = new Timer(0.7f, 3, [&]()-> void
			{
				Object* enemy =
					OBJECT->CreateObject("Enemy1_1", EEnemy, Vector2(enemy1_position_x, -300));

				enemy->AddComponent<Enemy1_1>();
				enemy1_position_x += 300;
			}, false);
		t_enemy1_spawn->TimerStart();
	}
}

void Scene_Stage1::WavePattern2(float current_coolTime, bool is_end)
{
	if (is_end)
	{
		pattern2 = true;
	}

	else if (pattern2)
	{
		Object* object[4];
		Enemy1_2* enemies[4];

		for (int i = 0; i < 4; i++)
		{
			object[i] = OBJECT->CreateObject("Enemy1_2", EEnemy, enemy2_position[i % 2]);
			enemies[i] = object[i]->AddComponent<Enemy1_2>();
			enemies[i]->SetEnemy(i);
		}

		pattern2 = false;
	}
}

void Scene_Stage1::WavePattern3(float current_coolTime, bool is_end)
{
	WavePattern1(current_coolTime, is_end);
	WavePattern2(current_coolTime, is_end);
}

void Scene_Stage1::WavePattern4(float current_coolTime, bool is_end)
{
	if (is_end)
	{
		t_enemy3_spawn = null;
	}
	else if (!t_enemy3_spawn)
	{
		OBJECT->CreateObject("Enemy1_3", EEnemy, Vector2(200, -50))
			->AddComponent<Enemy1_3>();

		t_enemy3_spawn = new Timer(3, 0, [&]()->void
			{
				OBJECT->CreateObject("Enemy1_3", EEnemy, Vector2(1400, -50))
					->AddComponent<Enemy1_3>();
			});
	}
}
