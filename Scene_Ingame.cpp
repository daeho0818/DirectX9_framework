#include "DXUT.h"
#include "Scene_Ingame.h"

Scene_Ingame::Scene_Ingame()
{
}

Scene_Ingame::~Scene_Ingame()
{
}

void Scene_Ingame::Init()
{
	m_playerObject = OBJECT->CreateObject("Player", ObjType::EPlayer, CENTER);
	m_player = m_playerObject->AddComponent<Player>();
}

void Scene_Ingame::Update()
{
	srand(time(NULL));

	if (GetKeyDown('E'))
	{
		var enemy = OBJECT->CreateObject("Enemy", ObjType::EEnemy, Vector2(rand() % 1920, -50));
		enemy->AddComponent<TestEnemy>();
	}
}

void Scene_Ingame::Render()
{
}

void Scene_Ingame::UIRender()
{
}

void Scene_Ingame::Release()
{
}
