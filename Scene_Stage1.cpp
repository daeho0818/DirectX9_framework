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

	enemy2_position[0] = Vector2(-50, 50);
	enemy2_position[1] = Vector2(WINSIZEX + 50, 50);

	enemy3_spawn_positions[0] = Vector2(1400, -50);
	enemy3_spawn_positions[1] = Vector2(400, -50);
	enemy3_spawn_positions[2] = Vector2(800, -50);

	pattern5 = false;

	pattern_helper->SetPattern(0, 10, 5, [&](float current_coolTime, bool is_end)->void
		{
			WavePattern1(current_coolTime, is_end);
		});
	pattern_helper->SetPattern(1, 7, 5, [&](float current_coolTime, bool is_end)->void
		{
			WavePattern2(current_coolTime, is_end);
		});
	pattern_helper->SetPattern(2, 10, 5, [&](float current_coolTime, bool is_end)->void
		{
			WavePattern3(current_coolTime, is_end);
		});
	pattern_helper->SetPattern(3, 8, 5, [&](float current_coolTime, bool is_end)->void
		{
			WavePattern4(current_coolTime, is_end);
		});
	pattern_helper->SetPattern(4, 35, 5, [&](float current_coolTime, bool is_end)->void
		{
			WavePattern5(current_coolTime, is_end);
		});

	// m_bossObject = OBJECT->CreateObject("Boss", ObjType::EEnemy, Vector2(WINSIZEX / 2, -300));
	// m_boss = m_bossObject->AddComponent<Boss1_1>();

	boss_appear_count = 120;

	scroll_helper = new ScrollHelper(IMAGE->FindImage("Background_1"));

	boss_appear_timer = new Timer(1, boss_appear_count, [&]()->void {boss_appear_count--; }, false);
	boss_appear_timer->TimerStart();
}

void Scene_Stage1::Update()
{
	srand(time(NULL));

	pattern_helper->Update();
	scroll_helper->Update();

	sprintf(boss_appear_str, "%d : %02d", boss_appear_count / 60, boss_appear_count % 60);
}

void Scene_Stage1::Render()
{
	scroll_helper->Render();
}

void Scene_Stage1::UIRender()
{
	RENDER->TextRender("보스 등장까지", Vector2(WINSIZEX / 2, 50));
	RENDER->TextRender(boss_appear_str, Vector2(WINSIZEX / 2, 110), 75);
}

void Scene_Stage1::Release()
{
	SAFE_DELETE(pattern_helper);
	SAFE_DELETE(scroll_helper);

	if (t_enemy1_spawn)
		t_enemy1_spawn->ShutTimer();
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
				Object* object =
					OBJECT->CreateObject("Enemy1_1", EEnemy, Vector2(enemy1_position_x, -300));
				object->AddComponent<Enemy1_1>();

				enemy1_position_x += 300;
			}, false);
		t_enemy1_spawn->TimerStart();
	}
}

void Scene_Stage1::WavePattern2(float current_coolTime, bool is_end)
{
	if (is_end)
	{
		pattern2 = false;
	}
	else if (!pattern2)
	{
		Object* object[4];
		Enemy1_2* enemies[4];

		for (int i = 0; i < 4; i++)
		{
			object[i] = OBJECT->CreateObject("Enemy1_2", EEnemy, enemy2_position[i % 2]);
			enemies[i] = object[i]->AddComponent<Enemy1_2>();
			enemies[i]->SetEnemy(i);
		}

		pattern2 = true;
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
		enemy3_spawn_count = 0;
		t_enemy3_spawn = null;
	}
	else if (t_enemy3_spawn == null)
	{
		Object* object = OBJECT->CreateObject("Enemy1_3", EEnemy, Vector2(200, -50));
		object->AddComponent<Enemy1_3>();

		t_enemy3_spawn = new Timer(2, 2, [&]()->void
			{
				Object* object = OBJECT->CreateObject("Enemy1_3", EEnemy,
					enemy3_spawn_positions[enemy3_spawn_count++]);
				object->AddComponent<Enemy1_3>();
			});

		t_enemy3_spawn->TimerStart();
	}
}

void Scene_Stage1::WavePattern5(float current_coolTime, bool is_end)
{
	if (is_end)
	{
		pattern5 = false;
	}
	else if (!pattern5)
	{
		for (int i = 0; i < 2; i++)
		{
			Object* object = OBJECT->CreateObject("Enemy1_4", EEnemy, Vector2(WINSIZEX / 2, 50));
			Enemy1_4* enemy = object->AddComponent<Enemy1_4>();
			enemy->SetEnemy(m_player, i);
		}

		pattern5 = true;
	}
}
