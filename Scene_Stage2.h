#pragma once
#include "Boss2_1.h"
class Scene_Stage2 : public Scene
{
public:
	Scene_Stage2();
	~Scene_Stage2();

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	// objects
	Object* m_playerObject = nullptr;
	Player* m_player = nullptr;

	Object* m_bossObject = nullptr;
	Boss2_1* m_boss = null;
};

