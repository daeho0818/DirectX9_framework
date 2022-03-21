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

	var image = IMAGE->FindImage("Enemy2");
	renderer->SetRenderer(image, D3DXCOLOR(1, 1, 1, 1));

	var img_info = image->info;
	collider->SetCollider(img_info.Width / 3 * 2, img_info.Height / 3 * 2);

	m_transform->m_localScale = Vector2(0.5f, 0.5f);

	sin_value = 0;

	move_able = false;

	bullet_image = IMAGE->FindImage("Bullet_Enemy_2");

	m_object->OnCollisionEnter = [&](Object* other) -> void
	{
		if (other->m_type == EP_Bullet)
		{
			m_object->HitAnimation(D3DXCOLOR(1, 0, 0, 1));
			m_object->m_hp--;
		}
		else if (other->m_type == EPlayer)
		{
			m_object->is_destroy_check = true;
		}
	};

	m_object->OnDestroy = [&]()->void
	{
		PARTICLE->AddParticleAnim(IMAGE->MakeAnimation("Explosion"), m_transform->m_position, 0.01f);
	};

	m_object->m_hp = m_object->m_maxHp = 3;

	wait_timer = new Timer(5, 0, [&]()->void
		{
			move_able = true;
		});
	wait_timer->TimerStart();

	m_object->fire_helper = new FireHelper();
}

void Enemy1_2::Update()
{
	m_object->fire_helper->Update();

	if (sin_value < 90)
	{
		sin_value += DELTA * 50;

		m_transform->Translate(Vector2(
			oper_value * cos(D3DXToRadian(sin_value)),
			2 * sin(D3DXToRadian(sin_value))) * DELTA * 100);
	}

	if (move_able)
	{
		m_transform->Translate(m_transform->down * DELTA * move_speed);
	}

	m_object->fire_helper->Fire(m_transform->m_position, bullet_interval,
		m_transform->down, "Enemy1_2 Bullet", EE_Bullet, bullet_speed, bullet_image);
}

void Enemy1_2::Render()
{
}

void Enemy1_2::UIRender()
{
}

void Enemy1_2::Release()
{
	if (wait_timer)
		wait_timer->ShutTimer();
}

void Enemy1_2::SetEnemy(int index)
{
	m_index = index;

	if (index == 0 || index == 1)
	{
		oper_value = 4 * (index == 1 ? -1 : 1);
		move_speed = 500;
		bullet_speed = 7;
		bullet_interval = 0.5f;
	}
	else if (index == 2 || index == 3)
	{
		oper_value = 8 * (index == 3 ? -1 : 1);
		move_speed = 600;
		bullet_speed = 15;
		bullet_interval = 0.25f;
	}
}