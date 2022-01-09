#pragma once
#include "Boss2_1.h"
class Scene_Stage2 : public Scene
{
public:
	Scene_Stage2();
	~Scene_Stage2();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	Object* m_bossObject = nullptr;
	Boss2_1* m_boss = null;
};

