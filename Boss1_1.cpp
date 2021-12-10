#include "DXUT.h"
#include "Boss1_1.h"

Boss1_1::Boss1_1(Object* object)
	:Component(object)
{
}

Boss1_1::~Boss1_1()
{
	SAFE_DELETE(pattern_helper);
}

void Boss1_1::Init()
{
	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();

	renderer->Setting(IMAGE->FindImage("Main_BG_Moon"), D3DXCOLOR(1, 1, 1, 1));

	bullet_image = IMAGE->FindImage("bullet_player");

	is_spawned = false;

	m_object->OnCollisionEnter = [&](Object* object)->void
	{
		if (!is_spawned) return;
	};

	bullet_pool = new	 BulletPool<Bullet>("Enemy Bullet",
		ObjType::EE_Bullet, 0, bullet_image, D3DXCOLOR(1, 1, 1, 1));
}

void Boss1_1::Update()
{
	if (!is_spawned)
	{
		SpawnAnimation();
		return;
	}

	bullet_pool->Update();

	if (GetKey('F'))
		Pattern2(0, false);

	if (GetKey(VK_LEFT))
		m_transform->Translate(m_transform->left * DELTA * 500);
	if (GetKey(VK_RIGHT))
		m_transform->Translate(m_transform->right * DELTA * 500);
	if (GetKey(VK_UP))
		m_transform->Translate(m_transform->up * DELTA * 500);
	if (GetKey(VK_DOWN))
		m_transform->Translate(m_transform->down * DELTA * 500);

	pattern_helper->Update();
}

void Boss1_1::Render()
{
}

void Boss1_1::UIRender()
{
}

void Boss1_1::Release()
{
	SAFE_DELETE(bullet_pool);
}

Vector2 direction;
float sin_value = 0;
float devide_value = 5;
void Boss1_1::Pattern1(float current_count, bool is_end)
{
	if (is_end)
	{
		devide_value = 2;
	}

	else if (current_count >= 5)
		devide_value = 0.5f;

	sin_value += DELTA * 500;

	direction.y = m_transform->down.y;
	direction.x += sin(D3DXToRadian(sin_value)) / devide_value;

	Bullet* bullet;

	bullet = bullet_pool->GetBullet(m_transform->m_position);
	if (!bullet) return;

	bullet->SetBullet(*D3DXVec2Normalize(&direction, &direction), 3, bullet_image, bullet_pool);
}

Vector2 target_position;
float lerp_percent;
bool is_pattern2 = true;
void Boss1_1::Pattern2(float current_count, bool is_end)
{
	if (is_end)
	{
		is_pattern2 = true;
		return;
	}
	if (!is_pattern2) return;

	if (current_count < 5)
	{
		target_position = Vector2(WINSIZEX / 2, 50);
		lerp_percent = 0.01f;
	}
	else
	{
		target_position = Vector2(WINSIZEX / 2, 300);
		lerp_percent = 0.2f;

		if (D3DXVec2Length(&(target_position - m_transform->m_position)) <= 1.0f)
		{
			lerp_percent = 0;

			CircleBullet(1, 5);
			CircleBullet(2, 4);
			CircleBullet(3, 3);

			CAMERA->ShakingCamera(5, 2, true);

			is_pattern2 = false;
		}
	}

	D3DXVec2Lerp(&m_transform->m_position, &m_transform->m_position,
		&target_position, lerp_percent);
}

void Boss1_1::CircleBullet(float speed, float interval)
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

void Boss1_1::SpawnAnimation()
{
	D3DXVec2Lerp(&m_transform->m_position, &m_transform->m_position,
		&Vector2(WINSIZEX / 2, 300), 0.01f);

	if (D3DXVec2Length(
		&(Vector2(WINSIZEX / 2, 300) - m_transform->m_position)) <= 1)
	{
		pattern_helper->SetPattern(1, 7, 5, [&](float current_count, bool is_end)->void { Pattern1(current_count, is_end); });
		pattern_helper->SetPattern(0, 6, 5, [&](float current_count, bool is_end)->void
			{ Pattern2(current_count, is_end); });

		is_spawned = true;
	}
}
