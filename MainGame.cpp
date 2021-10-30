#include "DXUT.h"
#include "MainGame.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	SCENE->AddScene("Scene_Title", new Scene_Title());
	SCENE->ChangeScene("Scene_Title");

	SCENE->Init();
	CAMERA->Init();
}

void MainGame::Update()
{
	SCENE->Update();
	SOUND->Update();
	CAMERA->Update();
}

void MainGame::Render()
{
	SCENE->Render();
}

void MainGame::UIRender()
{
	SCENE->UIRender();
}

void MainGame::Release()
{
	SCENE->Release();
	SOUND->StopAll();

	SceneManager::Destroy();
}

void MainGame::Begin()
{
	RENDER->Begin();
}

void MainGame::End()
{
	RENDER->End();
}

void MainGame::Lost()
{
	RENDER->Lost();
}

void MainGame::Reset()
{
	RENDER->Reset();
}
