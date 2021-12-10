#pragma once
template<typename T>
class BulletPool
{
public:
	BulletPool(string bullet_name, ObjType bullet_type, float fire_range,
		Image* bullet_image, D3DXCOLOR bullet_color)
		:m_bulletName(bullet_name), m_bulletType(bullet_type), m_fireRange(fire_range),
		m_bulletImage(bullet_image), m_bulletColor(bullet_color)
	{
		current_count = 0;
	}
	~BulletPool() { m_bullets.clear(); }

	T* GetBullet(Vector2 position)
	{
		if (current_count < m_fireRange)
			return null;

		T* bullet;

		if (!m_bullets.empty())
		{
			bullet = m_bullets.back();
			m_bullets.pop_back();

			bullet->m_transform->m_position = position;
			bullet->m_object->SetActive(true);
		}
		else
		{
			Object* object = OBJECT->CreateObject(m_bulletName, m_bulletType, position);
			bullet = object->AddComponent<T>();
		}

		current_count = 0;
		return bullet;
	}
	void ReturnBullet(T* bullet)
	{
		bullet->m_object->SetActive(false);
		m_bullets.push_back(bullet);
	}
	void Update()
	{
		current_count += DELTA;
	}

private:
	vector<T*> m_bullets;

	string m_bulletName;
	ObjType m_bulletType;

	Image* m_bulletImage;
	D3DXCOLOR m_bulletColor;

	float m_fireRange;
	float current_count;
};