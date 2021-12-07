#include "DXUT.h"
#include "Boss1_1.h"

Boss1_1::Boss1_1(Object* object)
	:Component(object)
{
}

Boss1_1::~Boss1_1()
{
}

void Boss1_1::Init()
{
	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();

	renderer->Setting(IMAGE->FindImage("Main_BG_Moon"), D3DXCOLOR(1, 1, 1, 1));

	bullet_image = IMAGE->FindImage("bullet_player");

	m_object->OnCollisionEnter = [&](Object* object)->void
	{

	};

	b_pattern1 = true;
}

void Boss1_1::Update()
{
	if (GetKeyDown('F'))
		CircleBullet(3, 5);

	if (GetKey(VK_LEFT))
		m_transform->Translate(m_transform->left * DELTA * 500);
	if (GetKey(VK_RIGHT))
		m_transform->Translate(m_transform->right * DELTA * 500);
	if (GetKey(VK_UP))
		m_transform->Translate(m_transform->up * DELTA * 500);
	if (GetKey(VK_DOWN))
		m_transform->Translate(m_transform->down * DELTA * 500);

	if (b_pattern1)
	{
		Pattern1();
	}
	else
	{
		if (t_pattern1 == nullptr)
		{
			t_pattern1 = new Timer(10, 0, [&]()->void
				{
					b_pattern1 = true;
					t_pattern1 = nullptr;
				});
			t_pattern1->TimerStart();
		}
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

float direction_x = -0.5f;
float sin_value = 0;
float devide_value = 50;
void Boss1_1::Pattern1()
{
	if (t_pattern1 == nullptr)
	{
		t_pattern1 = new Timer(7, 0, [&]()->void
			{
				b_pattern1 = false;
				devide_value = 50;
				sin_value = 0;
				direction_x = -0.5f;
				t_pattern1 = nullptr;
			});
		t_pattern1->TimerStart();
	}

	if (t_pattern1->GetTime() >= 5)
		devide_value = 20;

	sin_value += DELTA * 100;

	direction_x += sin(D3DXToRadian(sin_value)) / devide_value;

	Object* object;
	Bullet* bullet;

	object = OBJECT->CreateObject("Normal_Bullet", ObjType::EE_Bullet, m_transform->m_position);
	bullet = object->AddComponent<Bullet>();
	bullet->SetBullet(Vector2(direction_x, 1), 3, bullet_image);

}

void Boss1_1::Pattern2()
{
}

void Boss1_1::CircleBullet(float speed, float interval)
{
	Vector2 direction;
	Object* object;
	Bullet* bullet;
	for (int i = 0; i < 360; i += 1 * interval)
	{
		object = OBJECT->CreateObject("Normal_Bullet", ObjType::EE_Bullet, m_transform->m_position);
		bullet = object->AddComponent<Bullet>();
		bullet->SetBullet(Vector2(cos(D3DXToRadian(i)), sin(D3DXToRadian(i))), speed, bullet_image);
	}
}
