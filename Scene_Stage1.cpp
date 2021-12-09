#include "DXUT.h"
#include "Scene_Stage1.h"

Scene_Stage1::Scene_Stage1()
{
}

Scene_Stage1::~Scene_Stage1()
{
}

int position_x;
void Scene_Stage1::Init()
{
	pattern_helper = new	PatternHelper();

	m_playerObject = OBJECT->CreateObject("Player", ObjType::EPlayer, CENTER);
	m_player = m_playerObject->AddComponent<Player>();

	pattern_helper->SetPattern(0, 3, 10, [&](float current_coolTime, bool is_end)->void
		{
			if (is_end)
			{
				position_x = WINSIZEX / 2 - 300;
				t_enemy1_spawn = null;
			}
			else if (t_enemy1_spawn == null)
			{
				position_x = WINSIZEX / 2 - 300;

				t_enemy1_spawn = new Timer(0.7f, 3, [&]()-> void
					{
						Object* enemy =
							OBJECT->CreateObject("Enemy", ObjType::EEnemy, Vector2(position_x, -300));

						enemy->AddComponent<Enemy1_1>(); position_x += 300;
					}, false);
				t_enemy1_spawn->TimerStart();
			}
		});

	// m_bossObject = OBJECT->CreateObject("Boss", ObjType::EEnemy, Vector2(WINSIZEX / 2, -300));
	// m_boss = m_bossObject->AddComponent<Boss1_1>();
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
