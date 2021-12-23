#include "DXUT.h"
#include "Enemy1_4.h"

Enemy1_4::Enemy1_4(Object* object)
	:Component(object)
{
}

Enemy1_4::~Enemy1_4()
{
}

void Enemy1_4::Init()
{
	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();
	var image = IMAGE->FindImage("Enemy1_1");
	renderer->Setting(image, D3DXCOLOR(1, 1, 1, 1));

	reflect_count = 0;

	m_transform->m_localScale = Vector2(0.7f, 0.7f);

	m_object->fire_helper = new FireHelper();

	bullet_image = IMAGE->FindImage("Bullet_Enemy_1");
}

void Enemy1_4::Update()
{
	m_object->fire_helper->Update();

	m_transform->Translate(move_direction * DELTA * 200);

	if (reflect_count < 3)
		if ((m_transform->m_position.x > WINSIZEX - 50 && move_direction == m_transform->right) ||
			(m_transform->m_position.x < 0 + 50 && move_direction == m_transform->left))
		{
			move_direction *= -1;
			reflect_count++;
		}

	Vector2 direction = m_player->m_transform->m_position - m_transform->m_position;
	m_object->fire_helper->Fire(m_transform->m_position, 0.5f, *D3DXVec2Normalize(&direction, &direction), "Enemy1_4 Bullet", EE_Bullet, 7, bullet_image);
}

void Enemy1_4::Render()
{
}

void Enemy1_4::UIRender()
{
}

void Enemy1_4::Release()
{
}

void Enemy1_4::SetEnemy(Player* player, int enemy_index)
{
	move_direction = enemy_index == 0 ? m_transform->right : m_transform->left;
	m_player = player;
}
