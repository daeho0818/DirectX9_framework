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
	m_playerObject = OBJECT->CreateObject("Player", ObjType::EPlayer, CENTER);
	m_player = m_playerObject->AddComponent<Player>();
}

void Scene_Title::Update()
{
	if (DXUTIsKeyDown(VK_RETURN))
	{
		SCENE->ChangeScene("Scene_Loading");
	}
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
