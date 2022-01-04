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
	renderer = m_object->AddComponent<RendererC>();
	collider = m_object->AddComponent<BoxColliderC>();

	var image = IMAGE->FindImage("Boss1_1");
	renderer->SetRenderer(image, D3DXCOLOR(1, 1, 1, 1));

	var img_info = image->info;
	collider->SetCollider(img_info.Width / 3 * 2, img_info.Height / 3 * 2);

	bullet_image = IMAGE->FindImage("Bullet_Enemy_1");

	is_spawned = false;

	m_object->OnCollisionEnter = [&](Object* other)->void
	{
		if (!is_spawned) return;
		if (other->m_type == EP_Bullet)
		{
			m_object->HitAnimation(D3DXCOLOR(1, 0, 0, 1));
			m_object->m_hp--;
		}
	};
	m_object->m_hp = 250;
	m_object->wait_for_destroy = true;

	m_object->fire_helper = new FireHelper();
	pattern_helper = new PatternHelper();
}

void Boss1_1::Update()
{
	if (!is_spawned)
	{
		SpawnAnimation();
		return;
	}

	if (m_object->is_destroy_check) return;

	m_object->fire_helper->Update();

	pattern_helper->Update();

	if (GetKeyDown(VK_RETURN))
		Pattern3(0, false);
}

void Boss1_1::SpawnAnimation()
{
	D3DXVec2Lerp(&m_transform->m_position, &m_transform->m_position,
		&Vector2(WINSIZEX / 2, 300), 0.01f);

	if (D3DXVec2Length(&(Vector2(WINSIZEX / 2, 300) - m_transform->m_position)) <= 1)
	{
		pattern_helper->SetPattern(0, 7, 5, [&](float current_count, bool is_end)->void { Pattern1(current_count, is_end); });
		pattern_helper->SetPattern(1, 6, 5, [&](float current_count, bool is_end)->void { Pattern2(current_count, is_end); });
		pattern_helper->SetPattern(2, 17, 5, [&](float current_count, bool is_end)->void { Pattern3(current_count, is_end); });

		is_spawned = true;
	}
}

void Boss1_1::Render()
{
}

void Boss1_1::UIRender()
{
}

void Boss1_1::Release()
{
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

	D3DXVec2Normalize(&direction, &direction);

	m_object->fire_helper->Fire(m_transform->m_position, 0.1f,
		direction, "Boss1_1 Bullet", EE_Bullet, 3, bullet_image);
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

			m_object->fire_helper->CircleFire(m_transform->m_position, 9,
				"Boss1_1 Bullet", EE_Bullet, 1, bullet_image);

			m_object->fire_helper->CircleFire(m_transform->m_position, 8,
				"Boss1_1 Bullet", EE_Bullet, 2, bullet_image);

			m_object->fire_helper->CircleFire(m_transform->m_position, 7,
				"Boss1_1 Bullet", EE_Bullet, 3, bullet_image);


			CAMERA->ShakingCamera(5, 2, true);

			is_pattern2 = false;
		}
	}

	D3DXVec2Lerp(&m_transform->m_position, &m_transform->m_position,
		&target_position, lerp_percent);
}

void Boss1_1::Pattern3(float current_count, bool is_end)
{
	if (!t_pattern_3)
	{
		Vector2 position;
		Vector2 direction;
		Bullet* bullet;

		t_pattern_3 = new Timer(3, 5, [&]()->void
			{
				for (int _ = -1; _ < 2; _ += 2)
				{
					for (int i = 0; i < 360; i += 5)
					{
						position = m_transform->m_position + Vector2(cos(D3DXToRadian(i)) * 300, sin(D3DXToRadian(i)) * 300);
						position += Vector2(100, 0) * _;

						m_object->fire_helper->Fire(position, 0, Vector2(0, 0), "Boss1_1 P3 Bullet", EE_Bullet, 0, bullet_image);
					}
				}

				t_pattern_3_1 = new Timer(1, 0, [&]()->void
					{
						list<Object*> bullets = OBJECT->FindObject("Boss1_1 P3 Bullet");

						for (var iter : bullets)
						{
							bullet = iter->GetComponent<Bullet>();

							direction = m_player->m_transform->m_position - iter->m_transform->m_position;
							bullet->SetBullet(*D3DXVec2Normalize(&direction, &direction), 10, bullet_image);
						}
					});
				t_pattern_3_1->TimerStart();
			});
		t_pattern_3->TimerStart();
	}
}