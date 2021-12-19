#include "DXUT.h"
#include "Enemy1_3.h"

Enemy1_3::Enemy1_3(Object* object)
	:Component(object)
{
}

Enemy1_3::~Enemy1_3()
{
}

void Enemy1_3::Init()
{
	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();
	renderer->Setting(IMAGE->FindImage("Enemy_3"), D3DXCOLOR(1, 1, 1, 1));
	
	m_transform->m_localScale = Vector2(0.5f, 0.5f);

	bullet_image = IMAGE->FindImage("Bullet_Enemy_3");

	bullet_pool = new BulletPool<Bullet>("Enemy1_3 Bullet", EE_Bullet, 0, bullet_image);

	move_able = true;
}

void Enemy1_3::Update()
{
	bullet_pool->Update();

	if (move_able)
		m_transform->Translate(m_transform->down * DELTA * 100);

	if (m_transform->m_position.y >= WINSIZEY / 2)
	{
		if (wait_timer != nullptr)
		{
			CircleBullet(20, 10);
			move_able = false;
			wait_timer = new Timer(2, 0, [&]()->void {move_able = true; });
		}
	}
}

void Enemy1_3::Render()
{
}

void Enemy1_3::UIRender()
{
}

void Enemy1_3::Release()
{
}

void Enemy1_3::CircleBullet(float speed, float interval)
{
	Vector2 direction;
	Object* object;
	Bullet* bullet;

	int fireCount = 0;
	for (int i = 0; i < 360; i += 1 * interval)
	{
		bullet = bullet_pool->GetBullet(m_transform->m_position);
		if (!bullet)
			return;

		bullet->SetBullet(Vector2(cos(D3DXToRadian(i)), sin(D3DXToRadian(i))), speed, bullet_image, bullet_pool);
		fireCount++;
	}
}