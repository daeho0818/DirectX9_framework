#pragma once
#include "BulletPool.h"
class Bullet : public Component
{
public:
	Bullet(Object* object);
	~Bullet();

	void SetBullet(Vector2 direction, float move_speed, Image* image,
		BulletPool<Bullet>* bullet_pool, D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1));

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void ReturnBullet();

	BulletPool<Bullet>* bullet_pool;

private:
	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	const Vector2* m_position = nullptr;
	Vector2 m_direction;

	bool is_set;
	float m_moveSpeed = 0;

};