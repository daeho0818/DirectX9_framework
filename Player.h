#pragma once
#include "RendererC.h"
#include "BoxColliderC.h"
#include "BulletPool.h"
#include "Object.h"
class Player : public Component
{
	friend class ObjectManager;
public:
	Player(Object* object);
	~Player();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	Image* bullet_image = nullptr;

	RECT move_range;
	const Vector2* m_position = nullptr;

	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	Timer* destroy_timer = nullptr;

	float move_speed;
	float fire_range;
};

#include "Bullet.h"