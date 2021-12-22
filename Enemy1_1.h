#pragma once
#include "BulletPool.h"
class Enemy1_1 : public Component
{
public:
	Enemy1_1(Object* object);
	~Enemy1_1();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	Image* bullet_image = nullptr;

	Timer* wait_timer = nullptr;

	bool move_able;
};