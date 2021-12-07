#pragma once
#include "Player.h"
#include "Boss1_1.h"
#include "TestEnemy.h"
class Scene_Stage1 : public Scene
{
public:
	Scene_Stage1();
	~Scene_Stage1();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	Object* m_playerObject;
	Player* m_player;

	Object* m_bossObject;
	Boss1_1* m_boss;

};
