#pragma once
#include "RendererC.h"
#include "BoxColliderC.h"
#include "Object.h"
class Player : public Component
{
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
	void ChkMoveRange();
	void Fire();

	Image* bullet_image;

	RECT move_range;
	const Vector2* m_position;

	BoxColliderC* collider;
	RendererC* render;

	float move_speed;
	float first_fire_count;
	float current_fire_count;
	float fire_range;
};

#include "Bullet.h"