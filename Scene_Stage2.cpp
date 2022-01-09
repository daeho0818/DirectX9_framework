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
	m_bossObject = OBJECT->CreateObject("Boss2_1", EBoss, CENTER);
	m_boss = m_bossObject->AddComponent<Boss2_1>();
	m_boss->m_transform->m_localScale = Vector2(0, 0);
}

void Scene_Stage2::Update()
{
	D3DXVec2Lerp(&(m_boss->m_transform->m_localScale), &(m_boss->m_transform->m_localScale), &Vector2(1, 1), DELTA);
}

void Scene_Stage2::Render()
{
}

void Scene_Stage2::UIRender()
{
}

void Scene_Stage2::Release()
{
}
