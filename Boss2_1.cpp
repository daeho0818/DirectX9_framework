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

	m_object->fire_helper = new	FireHelper();
	pattern_helper = new PatternHelper();
}

void Boss2_1::Update()
{
	if (!is_spawned)
	{
		SpawnAnimation();
		return;
	}

	if (anim_complete_count < 4)
	{
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

void Boss2_1::SpawnAnimation()
{
	D3DXVec2Lerp(&m_transform->m_position, &m_transform->m_position,
		&Vector2(WINSIZEX / 2, 300), 0.01f);

	if (D3DXVec2Length(&(Vector2(WINSIZEX / 2, 300) - m_transform->m_position)) <= 1)
	{
		Object* cannon_object[4];
		Vector2 localPositions[4] = { Vector2(-150, -90), Vector2(150, -90), Vector2(-150, 150), Vector2(150,  150) };
		string names[4] = { "Boss2_1_LTop", "Boss2_1_RTop", "Boss2_1_LBottom", "Boss2_1_RBottom" };
		float rotation_z[4] = { 135, -135, 45, -45 };

		for (int i = 0; i < 4; i++)
		{
			cannon_object[i] = OBJECT->CreateObject(names[i], EBoss, m_transform->m_position + localPositions[i]);
			cannons.push_back(cannon_object[i]->AddComponent<Cannon>());
			cannons[i]->SetCannon(this, IMAGE->FindImage(names[i]), i);
			cannons[i]->m_transform->m_rotationZ = rotation_z[i];
		}

		is_spawned = true;
	}
}

void Boss2_1::ReleaseCannon(int index)
{
	cannons[index] = null;
}

void Boss2_1::Render()
{
}

void Boss2_1::UIRender()
{
}

void Boss2_1::Release()
{
	for (var cannon : cannons)
		SAFE_DELETE(cannon);
	cannons.clear();
}

void Boss2_1::Pattern1(float current_count, bool is_end)
{
	if (is_end)
	{
		float rotation_z[4] = { 135, -135, 45, -45 };

		for (int i = 0; i < 4; i++)
			if (cannons[i] != null)
				cannons[i]->m_transform->m_rotationZ = rotation_z[i];
	}
	else
	{
		Vector2 direction;
		for (int i = 0; i < 4; i++)
		{
			if (cannons[i] != null)
			{
				direction = m_player->m_transform->m_position - cannons[i]->m_transform->m_position;
				D3DXVec2Normalize(&direction, &direction);

				cannons[i]->Rotation(m_player->m_transform->m_position);
				cannons[i]->m_object->fire_helper->Fire(cannons[i]->m_transform->m_position, 0.25f, direction, cannons[i]->m_object->m_name + " Bullet", EE_Bullet, 7, bullet_image);
			}
		}
	}
}

void Boss2_1::SetAllPatterns()
{
	pattern_helper = new PatternHelper();

	pattern_helper->SetPattern(0, 5, 5, [&](float current_count, bool is_end)->void { Pattern1(current_count, is_end); });
}
