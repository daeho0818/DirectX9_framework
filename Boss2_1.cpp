#include "DXUT.h"
#include "Boss2_1.h"

Boss2_1::Boss2_1(Object* object)
	:Component(object)
{
}

Boss2_1::~Boss2_1()
{
}

void Boss2_1::Init()
{
	renderer = m_object->AddComponent<RendererC>();
	collider = m_object->AddComponent<BoxColliderC>();

	var image = IMAGE->FindImage("Boss2_1");
	renderer->SetRenderer(image, D3DXCOLOR(1, 1, 1, 1));

	var img_info = image->info;
	collider->SetCollider(img_info.Width / 2, img_info.Height / 2);

	Object* cannon_object[4];
	Vector2 localPositions[4] = { Vector2(-50, -30), Vector2(50, -30), Vector2(-50, -30), Vector2(50, 30) };
	string names[4] = { "Cannon_LTop", "Cannon_RTop", "Cannon_LBottom", "Cannon_RBotton" };

	for (int i = 0; i < 4; i++)
	{
		cannon_object[i] = OBJECT->CreateObject(names[i], EBoss, m_transform->m_position + localPositions[i]);
		cannons[i] = cannon_object[i]->AddComponent<Cannon>();
		cannons[i]->SetCannon(IMAGE->FindImage(names[i]));
	}

	m_object->m_hp = 100;
}

void Boss2_1::Update()
{
}

void Boss2_1::Render()
{
}

void Boss2_1::UIRender()
{
}

void Boss2_1::Release()
{
}
