#include "DXUT.h"
#include "Enemy1_1.h"

Enemy1_1::Enemy1_1(Object* object)
	:Component(object)
{
}

Enemy1_1::~Enemy1_1()
{
}

void Enemy1_1::Init()
{
	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();

	renderer->Setting(IMAGE->FindImage("White"), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1));
	m_transform->m_scale = 0.5f;

	bullet_image = IMAGE->FindImage("bullet_player");

	check_time = fire_check_time = 0;
	is_fire = true;
}

void Enemy1_1::Update()
{
	if (m_transform->m_position.y < 380)
		D3DXVec2Lerp(&m_transform->m_position,
			&m_transform->m_position,
			&Vector2(m_transform->m_position.x, 400), DELTA);
	else
	{
		check_time += DELTA;
		if (check_time >= 3)
		{
			is_fire = false;

			m_transform->Translate(m_transform->down * DELTA * 500);
		}
	}

	if (is_fire)
	{
		fire_check_time += DELTA;
		Fire();
	}
}

void Enemy1_1::Render()
{
}

void Enemy1_1::UIRender()
{
}

void Enemy1_1::Release()
{
}

void Enemy1_1::Fire()
{
	if (fire_check_time > 0.25f)
	{
		fire_check_time = 0;
		Object* object = OBJECT->CreateObject("EBullet", ObjType::EE_Bullet, m_transform->m_position);
		Bullet* bullet = object->AddComponent<Bullet>();
		bullet->SetBullet(m_transform->down, 15, bullet_image);
	}
}
