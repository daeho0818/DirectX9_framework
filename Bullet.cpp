#include "DXUT.h"
#include "Bullet.h"

Bullet::Bullet(Object* object)
	:Component(object)
{
}

Bullet::~Bullet()
{
}

void Bullet::SetBullet(Vector2 direction, float move_speed, Image* image)
{
	m_direction = direction;
	m_moveSpeed = move_speed;

	renderer->Setting(image, D3DXCOLOR(1, 1, 1, 1));

	is_set = true;

	m_object->OnCollisionEnter = [&](Object* other)->void
	{
		if (other->m_type == ObjType::EEnemy)
		{
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

	m_object->CheckOut();
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
