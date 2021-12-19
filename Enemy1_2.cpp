#include "DXUT.h"
#include "Enemy1_2.h"

Enemy1_2::Enemy1_2(Object* object)
	:Component(object)
{
}

Enemy1_2::~Enemy1_2()
{
}

void Enemy1_2::Init()
{
	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();
	renderer->Setting(IMAGE->FindImage("Enemy_2"), D3DXCOLOR(1, 1, 1, 1));

	m_transform->m_localScale = Vector2(0.5f, 0.5f);

	sin_value = 0;

	oper_values[0] = 4;
	oper_values[1] = -4;
	oper_values[2] = 8;
	oper_values[3] = -8;

	move_able = false;

	bullet_image = IMAGE->FindImage("Bullet_Enemy_2");

	bullet_pool = new BulletPool<Bullet>("Enemy1_2 Bullet", EE_Bullet, 0.25f, bullet_image);

	wait_timer = new Timer(5, 0, [&]()->void
		{
			move_able = true;
		});
	wait_timer->TimerStart();
}

void Enemy1_2::Update()
{
	bullet_pool->Update();

	if (sin_value < 90)
	{
		sin_value += DELTA * 50;

		m_transform->Translate(Vector2(
			oper_values[m_index] * cos(D3DXToRadian(sin_value)),
			2 * sin(D3DXToRadian(sin_value))));
	}

	if (move_able)
	{
		m_transform->Translate(m_transform->down * DELTA * 500);
	}

	Fire();
}

void Enemy1_2::Render()
{
}

void Enemy1_2::UIRender()
{
}

void Enemy1_2::Release()
{
}

void Enemy1_2::SetEnemy(int index)
{
	m_index = index;
}

void Enemy1_2::Fire()
{
	Bullet* bullet = bullet_pool->GetBullet(m_transform->m_position);
	if (!bullet) return;

	bullet->SetBullet(m_transform->down, 15, bullet_image, bullet_pool);
}