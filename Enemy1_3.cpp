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
	renderer->Setting(IMAGE->FindImage("Enemy1_3"), D3DXCOLOR(1, 1, 1, 1));
	
	m_transform->m_localScale = Vector2(0.5f, 0.5f);

	bullet_image = IMAGE->FindImage("Bullet_Enemy_3");

	move_able = true;

	m_object->OnCollisionEnter = [&](Object* other) -> void
	{
		if (other->m_type == EP_Bullet)
		{
			m_object->HitAnimation(D3DXCOLOR(1, 0, 0, 1));
		}
	};

	m_object->fire_helper = new FireHelper();
}

void Enemy1_3::Update()
{
	m_object->fire_helper->Update();

	if (move_able)
		m_transform->Translate(m_transform->down * DELTA * 300);

	if (m_transform->m_position.y >= WINSIZEY / 2)
	{
		if (wait_timer == nullptr)
		{
			m_object->fire_helper->CircleFire(m_transform->m_position, 20, 
				"Enemy1_3 Bullet", EE_Bullet, 5, bullet_image);
			move_able = false;
			wait_timer = new Timer(2, 0, [&]()->void {move_able = true; });
			wait_timer->TimerStart();
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