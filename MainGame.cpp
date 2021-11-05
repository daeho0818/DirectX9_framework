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
	IMAGE->AddImage("Speed+", "Speed+");
	IMAGE->Loading();

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
	RENDER->Begin();

	SCENE->Render();
	CAMERA->Render();

	SCENE->UIRender();
	CAMERA->UIRender();

	RENDER->End();
}

void MainGame::UIRender()
{
	SCENE->UIRender();
}

void MainGame::Release()
{
	SCENE->Release();
	SOUND->StopAll();

	CameraManager::Destroy();
	ImageManager::Destroy();
	RenderManager::Destroy();
	SceneManager::Destroy();
	SoundManager::Destroy();

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
