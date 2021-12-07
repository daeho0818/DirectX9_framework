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

	timer = new Timer(1, 0, [&]()->void {Pattern1(); }, true);
	timer->TimerStart();
}

void Boss1_1::Update()
{
	if (GetKeyDown('F'))
		Pattern1();

	if (GetKey(VK_LEFT))
		m_transform->Translate(m_transform->left * DELTA * 500);
	if (GetKey(VK_RIGHT))
		m_transform->Translate(m_transform->right * DELTA * 500);
	if (GetKey(VK_UP))
		m_transform->Translate(m_transform->up * DELTA * 500);
	if (GetKey(VK_DOWN))
		m_transform->Translate(m_transform->down * DELTA * 500);
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

int range_min = 0;
int range_max = 30;
void Boss1_1::Pattern1()
{
	Vector2 direction;
	Object* object;
	Bullet* bullet;
	for (int i = 0; i < 360; i++)
	{
		if (i % 2 == 0 || (i > range_min && i < range_max)) continue;
		object = OBJECT->CreateObject("E_Bullet", ObjType::EE_Bullet, m_transform->m_position);
		bullet = object->AddComponent<Bullet>();
		bullet->SetBullet(Vector2(cos(i), sin(i)), 5, bullet_image);
	}
	range_min += 10;
	range_max += 10;
}

void Boss1_1::Pattern2()
{
}
