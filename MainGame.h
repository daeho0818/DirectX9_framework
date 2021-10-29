#pragma once
class MainGame
{
public:
	MainGame();
	~MainGame();

	void Init();
	void Update();
	void Render();
	void UIRender();
	void Release();

	void Begin();
	void End();
	void Lost();
	void Reset();
};

#include "Scene_Title.h"
