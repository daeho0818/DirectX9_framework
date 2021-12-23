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

	renderer->Setting(IMAGE->FindImage("Enemy1_1"), D3DXCOLOR(1, 1, 1, 1));
	m_transform->m_localScale = Vector2(0.5f, 0.5f);

	bullet_image = IMAGE->FindImage("Bullet_Enemy_1");

	move_able = true;

	m_object->fire_helper = new FireHelper();

	m_object->OnCollisionEnter = [&](Object* other) -> void
	{
		if (other->m_type == EP_Bullet)
		{
			m_object->HitAnimation(renderer, D3DXCOLOR(1, 0, 0, 1));
		}
	};
}

void Enemy1_1::Update()
{
	m_object->fire_helper->Update();

	m_object->fire_helper->Fire(m_transform->m_position, 0.5f,
		m_transform->down, "Enemy1_1 Bullet", EE_Bullet, 7, bullet_image);

	if (m_transform->m_position.y < 380)
		D3DXVec2Lerp(&m_transform->m_position,
			&m_transform->m_position,
			&Vector2(m_transform->m_position.x, 400), DELTA);
	else
	{
		if (!wait_timer && move_able)
		{
			move_able = false;
			wait_timer = new Timer(3, 0, [&]()->void {move_able = true; });
			wait_timer->TimerStart();
		}

		if (move_able)
			m_transform->Translate(m_transform->down * DELTA * 500);
	}
	if (GetKey(VK_F2))
		m_transform->m_rotationZ++;
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
