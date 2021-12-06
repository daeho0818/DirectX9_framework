#pragma once
#include "Player.h"
#include "TestEnemy.h"
class Scene_Ingame : public Scene
{
public:
	Scene_Ingame();
	~Scene_Ingame();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	Object* m_playerObject;
	Player* m_player;

};

