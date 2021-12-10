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

	bullet_pool = new BulletPool<Bullet>("Enemy1_1 Bullet", ObjType::EE_Bullet, 0.25f, bullet_image, D3DXCOLOR(1, 1, 1, 1));
}

void Enemy1_1::Update()
{
	bullet_pool->Update();
	Fire();

	if (m_transform->m_position.y < 380)
		D3DXVec2Lerp(&m_transform->m_position,
			&m_transform->m_position,
			&Vector2(m_transform->m_position.x, 400), DELTA);
	else
	{
		m_transform->Translate(m_transform->down * DELTA * 500);
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
	SAFE_DELETE(bullet_pool);
}

void Enemy1_1::Fire()
{
	Bullet* bullet = bullet_pool->GetBullet(m_transform->m_position);
	if (!bullet)
	{
		if (GetKeyDown('G'))
			OutputDebugStringW(L"ÀÀ¾Ö!");
		return;
	}
	bullet->SetBullet(m_transform->down, 15, bullet_image, bullet_pool);
}
