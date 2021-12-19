#include "DXUT.h"
#include "BulletPool.h"

BulletPool::BulletPool()
{
}

BulletPool::~BulletPool()
{
}

Bullet* BulletPool::GetBullet(Vector2 position, string bullet_name, ObjType bullet_type)
{
	Bullet* bullet;

	if (!m_bullets.empty())
	{
		bullet = m_bullets.back();
		m_bullets.pop_back();

		bullet->m_transform->m_position = position;
		bullet->m_object->SetActive(true);
	}
	else
	{
		Object* object = OBJECT->CreateObject(bullet_name, bullet_type, position);
		bullet = object->AddComponent<Bullet>();
	}

	return bullet;
}

void BulletPool::ReturnBullet(Bullet* bullet)
{
	bullet->m_object->SetActive(false);
	m_bullets.push_back(bullet);
}
