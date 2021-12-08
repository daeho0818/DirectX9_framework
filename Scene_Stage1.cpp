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
	m_playerObject = OBJECT->CreateObject("Player", ObjType::EPlayer, CENTER);
	m_player = m_playerObject->AddComponent<Player>();

	m_bossObject = OBJECT->CreateObject("Boss", ObjType::EEnemy, Vector2(WINSIZEX / 2, 500));
	m_boss = m_bossObject->AddComponent<Boss1_1>();
}

void Scene_Stage1::Update()
{
	srand(time(NULL));
}

void Scene_Stage1::Render()
{
}

void Scene_Stage1::UIRender()
{
}

void Scene_Stage1::Release()
{
}
