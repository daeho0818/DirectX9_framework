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
}

void Scene_Title::Update()
{
}

void Scene_Title::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Screen"), Vector2(0, 0), 0.5f);
}

void Scene_Title::UIRender()
{
}
void Scene_Title::Release()
{
}
