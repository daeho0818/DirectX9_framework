#include "DXUT.h"
#include "Scene_Title.h"

Scene_Title::Scene_Title()
{
}

Scene_Title::~Scene_Title()
{
}

void Scene_Title::Init()
{
	m_playerObject = OBJECT->CreateObject("Player", EPlayer, CENTER);
	m_player = m_playerObject->AddComponent<Player>();
}

void Scene_Title::Update()
{
}

void Scene_Title::Render()
{
}

void Scene_Title::UIRender()
{
}
void Scene_Title::Release()
{
}
