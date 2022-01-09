#pragma once
class MainGame
{
public:
	MainGame();
	~MainGame();

	void Init();
	void Update();
	void Render();
	void Release();

	void Begin();
	void End();
	void Lost();
	void Reset();

private:

};

#include "Scene_Loading.h"
#include "Scene_Title.h"
#include "Scene_Stage1.h"
#include "Scene_Stage2.h"
