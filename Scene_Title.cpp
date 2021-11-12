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
	m_player->m_object = m_playerObject;
}

void Scene_Title::Update()
{
}

void Scene_Title::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Screen"), CENTER, 0.3f, 1, false, D3DXCOLOR(0, 0, 0, 1));
}

void Scene_Title::UIRender()
{
	RENDER->CenterRender(IMAGE->FindImage("Screen"), Vector2(0, 0), 0.1f, 1, true);
}
void Scene_Title::Release()
{
}
