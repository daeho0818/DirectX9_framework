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

#include "Scene_Title.h"
#include "Scene_Loading.h"
