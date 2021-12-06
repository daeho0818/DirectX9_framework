#pragma once
#include "Player.h"
#include "TestEnemy.h"
class Scene_Ingame : public Scene
{
public:
	Scene_Ingame();
	~Scene_Ingame();

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	Object* m_playerObject;
	Player* m_player;

};

