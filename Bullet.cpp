#include "DXUT.h"
#include "Bullet.h"

Bullet::Bullet(Object* object)
	:Component(object)
{
}

Bullet::~Bullet()
{
}

void Bullet::SetBullet(Vector2 direction, float move_speed, Image* image,
	D3DXCOLOR color)
{
	m_direction = direction;
	m_moveSpeed = move_speed;

	renderer->Setting(image, color);

	is_set = true;

	m_object->OnCollisionEnter = [&](Object* other)->void
	{
		if (m_object->m_type == EP_Bullet && other->m_type == EEnemy)
		{
			if (m_object->ActiveSelf())
				m_object->is_destroy = true;
		}
	};

	m_transform->m_rotationZ = 90 + D3DXToDegree(atan2(direction.y, direction.x));
}

void Bullet::Init()
{
	is_set = false;
	m_position = &m_object->m_transform->m_position;

	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();
}

void Bullet::Update()
{
	if (is_set)
	{
		m_transform->m_position += m_direction * DELTA * 100 * m_moveSpeed;
	}
}

void Bullet::Render()
{
}

void Bullet::UIRender()
{
}

void Bullet::Release()
{
}

void Bullet::ReturnBullet()
{
	is_set = false;
	m_object->is_destroy = false;

	B_POOL->ReturnBullet(this);
}
