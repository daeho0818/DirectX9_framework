#pragma once
#include "BulletPool.h"
class Enemy1_1 : public Component
{
public:
	Enemy1_1(Object* object);
	~Enemy1_1();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	void Fire();

	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	Image* bullet_image = nullptr;

	Timer* wait_timer = nullptr;

	BulletPool<Bullet>* bullet_pool;

	bool move_able;
};