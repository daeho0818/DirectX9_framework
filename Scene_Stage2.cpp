#include "DXUT.h"
#include "Scene_Stage2.h"

Scene_Stage2::Scene_Stage2()
{
}

Scene_Stage2::~Scene_Stage2()
{
}

void Scene_Stage2::Init()
{
	m_boss = null;
	m_bossObject = null;
	t_enemy1_spawn = t_enemy3_spawn = player_destroy_animation = boss_destroy_animation = null;

	m_playerObject = OBJECT->CreateObject("Player", EPlayer, CENTER);
	m_player = m_playerObject->AddComponent<Player>();

	pattern2 = false;

	enemy2_position[0] = Vector2(-50, 50);
	enemy2_position[1] = Vector2(WINSIZEX + 50, 50);

	enemy3_spawn_positions[0] = Vector2(1400, -50);
	enemy3_spawn_positions[1] = Vector2(400, -50);
	enemy3_spawn_positions[2] = Vector2(800, -50);

	pattern5 = false;

	pattern_helper = new	PatternHelper();
	SetAllWavePatterns();

	boss_appear_count = 30;

	scroll_helper = new ScrollHelper(IMAGE->FindImage("Background_2"));

	boss_appear_timer = new Timer(1, boss_appear_count, [&]()->void
		{
			boss_appear_count--;

			if (boss_appear_count == 0)
			{
				m_bossObject = OBJECT->CreateObject("Boss2_1", EBoss, Vector2(WINSIZEX / 2, -300));
				m_boss = m_bossObject->AddComponent<Boss2_1>();
			}
		}, false);

	player_destroy_loop_count = 0;
	boss_destroy_loop_count = 0;

	boss_appear_timer->TimerStart();

	stage_text = "";

	stage_text_animation = new Timer(0.1f, complete_stage_text.size(), [&]()->void
		{
			if (text_index < complete_stage_text.size())
				stage_text += complete_stage_text[text_index++];
		}, false);

	player_hp_bg = IMAGE->FindImage("Player_Hp_Bg");
	player_hp_bar = IMAGE->FindImage("Player_Hp_Bar");

	stage_text_animation->TimerStart();
}

void Scene_Stage2::SetAllWavePatterns()
{
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
	pattern_helper->SetPattern(4, 10, 5, [&](float current_coolTime, bool is_end)->void
		{
			WavePattern5(current_coolTime, is_end);
		});
}

void Scene_Stage2::Update()
{
	srand(time(NULL));

	pattern_helper->Update();
	scroll_helper->Update();

	if (m_player->m_object->is_destroy_check && !m_boss->m_object->is_destroy_check)
	{
		if (!player_destroy_animation)
			DestroyAnimation(0);
	}

	else if (m_boss)
		if (m_boss->m_object->is_destroy_check && !m_player->m_object->is_destroy_check)
			if (!boss_destroy_animation)
				DestroyAnimation(1);

	sprintf(boss_appear_str, "%d : %02d", boss_appear_count / 60, boss_appear_count % 60);
}

void Scene_Stage2::DestroyAnimation(int index)
{
	(index == 0 ? player_destroy_animation : boss_destroy_animation) = new Timer(1, 6, [&, index]()->void
		{
			vector<Image*> explosion_amimation;
			Vector2 target_position;

			(index == 0 ? player_destroy_loop_count : boss_destroy_loop_count)++;

			switch ((index == 0 ? player_destroy_loop_count : boss_destroy_loop_count))
			{
			case 1:
				CAMERA->ZoomingCamera(2, 5);
				CAMERA->MovingCamera((index == 0 ? m_player->m_object : m_boss->m_object)->m_transform->m_position, 5);
				break;
			case 2:
				target_position = (index == 0 ? m_player->m_transform->m_position : m_boss->m_transform->m_position);
				explosion_amimation = IMAGE->MakeAnimation("Explosion");

				PARTICLE->AddParticleAnim(explosion_amimation, target_position, 0.01f);
				break;
			case 3:
				target_position = (index == 0 ? m_player->m_transform->m_position : m_boss->m_transform->m_position);
				explosion_amimation = IMAGE->MakeAnimation("Explosion");

				PARTICLE->AddParticleAnim(explosion_amimation, target_position, 0.01f, 1.5f);
				(index == 0 ? m_player->m_object : m_boss->m_object)->GetComponent<RendererC>()->SetImage(null);
				break;
			case 4:
				CAMERA->StopAction(0);
				CAMERA->StopAction(1);

				CAMERA->ZoomingCamera(1, 2);
				CAMERA->MovingCamera(CENTER, 5);
				break;
			case 5:
				break;
			case 6:
				SCENE->ChangeScene("Scene_Title");
				break;
			}
		});
	(index == 0 ? player_destroy_animation : boss_destroy_animation)->TimerStart();
}

void Scene_Stage2::Render()
{
	scroll_helper->Render();
}

void Scene_Stage2::UIRender()
{
	RENDER->TextRender(stage_text, Vector2(150, 75));
	RENDER->TextRender("보스 등장까지", Vector2(WINSIZEX / 2, 50));
	RENDER->TextRender(boss_appear_str, Vector2(WINSIZEX / 2, 110), 75);

	RECT rc =
	{
		0,
		0,
		player_hp_bar->info.Width * (m_player->m_object->m_hp / (float)m_player->m_object->m_maxHp),
		player_hp_bar->info.Height
	};
	RENDER->CenterRender(player_hp_bg, Vector2(275, 1030), Vector2(0.5f, 0.5f), 0, true);
	RENDER->CropRender(player_hp_bar, Vector2(275, 1030), rc, 0.5f, 0, true);
}

void Scene_Stage2::Release()
{
	SAFE_DELETE(pattern_helper);
	SAFE_DELETE(scroll_helper);

	if (t_enemy1_spawn)
		t_enemy1_spawn->ShutTimer();

	if (t_enemy3_spawn)
		t_enemy3_spawn->ShutTimer();

	if (boss_appear_timer)
		boss_appear_timer->ShutTimer();

	if (player_destroy_animation)
		player_destroy_animation->ShutTimer();

	if (boss_destroy_animation)
		boss_destroy_animation->ShutTimer();

	if (stage_text_animation)
		stage_text_animation->ShutTimer();
}

void Scene_Stage2::WavePattern1(float current_coolTime, bool is_end)
{
	if (is_end)
	{
		enemy1_position_x = WINSIZEX / 2 - 50;
		t_enemy1_spawn = null;
	}
	else if (t_enemy1_spawn == null)
	{
		enemy1_position_x = WINSIZEX / 2 - 600;

		t_enemy1_spawn = new Timer(0.7f, 5, [&]()-> void
			{
				Object* object =
					OBJECT->CreateObject("Enemy2_1", EEnemy, Vector2(enemy1_position_x, -300));
				object->AddComponent<Enemy2_1>();

				enemy1_position_x += 300;
			}, false);
		t_enemy1_spawn->TimerStart();
	}
}

void Scene_Stage2::WavePattern2(float current_coolTime, bool is_end)
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

void Scene_Stage2::WavePattern3(float current_coolTime, bool is_end)
{
	WavePattern1(current_coolTime, is_end);
	WavePattern2(current_coolTime, is_end);
}

void Scene_Stage2::WavePattern4(float current_coolTime, bool is_end)
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

void Scene_Stage2::WavePattern5(float current_coolTime, bool is_end)
{
	if (is_end)
	{
		pattern5 = false;
	}
	else if (!pattern5)
	{
		Vector2 positions[4] = { Vector2(WINSIZEX / 2, 50), Vector2(WINSIZEX / 2, 50), Vector2(0, 50), Vector2(WINSIZEX, 50) };
		for (int i = 0; i < 4; i++)
		{
			Object* object = OBJECT->CreateObject("Enemy1_4", EEnemy, positions[i]);
			Enemy1_4* enemy = object->AddComponent<Enemy1_4>();
			enemy->SetEnemy(m_player, i);
		}

		pattern5 = true;
	}
}
