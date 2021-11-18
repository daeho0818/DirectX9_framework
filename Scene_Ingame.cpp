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
