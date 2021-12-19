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
	BulletPool* bullet_pool, D3DXCOLOR color)
{
	m_direction = direction;
	m_moveSpeed = move_speed;
	this->bullet_pool = bullet_pool;

	renderer->Setting(image, color);

	is_set = true;

	m_object->OnCollisionEnter = [&](Object* other)->void
	{
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

void Bullet::ReturnBullet()
{
	is_set = false;

	m_transform->m_position = CENTER;
	m_object->is_destroy = false;

	bullet_pool->ReturnBullet(this);
}
