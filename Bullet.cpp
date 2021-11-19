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
	m_image = image;

	is_set = true;
}

bool Bullet::CheckOutRange()
{
	bool condition = (m_position->x < 0 || m_position->x >WINSIZEX ||
		m_position->y < 0 || m_position->y > WINSIZEY);

	return condition;
}

void Bullet::Init()
{
	is_set = false;
	m_position = &m_object->m_transform->m_position;
}

void Bullet::Update()
{
	if (is_set)
	{
		m_object->m_transform->m_position += m_direction * DELTA * 100 * m_moveSpeed;

		if (CheckOutRange())
		{
			m_object->is_destroy = true;
		}
	}
}

void Bullet::Render()
{
	if (is_set)
		RENDER->CenterRender(m_image, m_object->m_transform->m_position, m_object->m_transform->m_scale, m_object->m_transform->m_rotationZ);
}

void Bullet::UIRender()
{
}

void Bullet::Release()
{
}
