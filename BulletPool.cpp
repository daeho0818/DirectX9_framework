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
		bullet->m_object->m_name = bullet_name;
		bullet->m_transform->m_object->m_type = bullet_type;

		OBJECT->BulletInsertList(bullet->m_object, bullet_type);

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

void BulletPool::Release()
{
	m_bullets.clear();
}
