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

	var player_object = OBJECT->FindObject(EPlayer).front();
	m_player = player_object->GetComponent<Player>();

	bullet_image = IMAGE->FindImage("Bullet_Enemy_1");

	Object* cannon_object[4];
	Vector2 localPositions[4] = { Vector2(-150, -90), Vector2(150, -90), Vector2(-150, 150), Vector2(150,  150) };
	string names[4] = { "Boss2_1_LTop", "Boss2_1_RTop", "Boss2_1_LBottom", "Boss2_1_RBottom" };
	float rotation_z[4] = { 135, -135, 45, -45 };

	for (int i = 0; i < 4; i++)
	{
		cannon_object[i] = OBJECT->CreateObject(names[i], EBoss, m_transform->m_position + localPositions[i]);
		cannons[i] = cannon_object[i]->AddComponent<Cannon>();
		cannons[i]->SetCannon(IMAGE->FindImage(names[i]));
		cannons[i]->m_transform->m_rotationZ = rotation_z[i];
	}

	m_object->fire_helper = new	FireHelper();

	m_object->m_hp = 150;
}

void Boss2_1::Update()
{
	if (m_transform->m_localScale.x >= 0.99f && anim_complete_count < 4)
	{
		m_transform->m_localScale = Vector2(1, 1);
		anim_complete_count = 0;

		for (var iter : cannons)
		{
			D3DXVec2Lerp(&iter->m_transform->m_localScale, &iter->m_transform->m_localScale, &Vector2(1, 1), 0.1f);

			if (iter->m_transform->m_localScale.x >= 0.99f)
			{
				iter->m_transform->m_localScale = Vector2(1, 1);
				anim_complete_count++;
			}
		}

		if (anim_complete_count == 4) SetAllPatterns();
	}

	if (pattern_helper)
		pattern_helper->Update();
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

void Boss2_1::Pattern1(float current_count, bool is_end)
{
	if (is_end)
	{
		float rotation_z[4] = { 135, -135, 45, -45 };

		for (int i = 0; i < 4; i++)
			if (cannons[i])
				cannons[i]->m_transform->m_rotationZ = rotation_z[i];
	}
	else
	{
		Vector2 direction;
		for (var iter : cannons)
		{
			direction = m_player->m_transform->m_position - iter->m_transform->m_position;
			D3DXVec2Normalize(&direction, &direction);

			iter->Rotation(m_player->m_transform->m_position);
			iter->m_object->fire_helper->Fire(iter->m_transform->m_position, 0.25f, direction, iter->m_object->m_name + " Bullet", EE_Bullet, 7, bullet_image);
		}
	}
}

void Boss2_1::SetAllPatterns()
{
	pattern_helper = new PatternHelper();

	pattern_helper->SetPattern(0, 5, 5, [&](float current_count, bool is_end)->void { Pattern1(current_count, is_end); });
}
