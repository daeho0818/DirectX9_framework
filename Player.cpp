#include "DXUT.h"
#include "Player.h"

Player::Player(Object* object) : Component(object)
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_position = &(m_transform->m_position);
	m_transform->m_localScale = Vector2(0.5f, 0.5f);

	move_speed = 1000;
	fire_range = 0.5f;
	m_object->m_hp = 20;

	invincibility = false;

	m_object->OnCollisionEnter = [&](Object* other)->void
	{
		if (other->m_type == EE_Bullet || other->m_type == EEnemy)
		{
			if (!invincibility)
			{
				m_object->HitAnimation(D3DXCOLOR(1, 0, 0, 1));
				m_object->m_hp--;
			}
		}
	};
	m_object->wait_for_destroy = true;

	bullet_image = IMAGE->FindImage("Bullet_Player");

	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();

	var image = IMAGE->FindImage("Player");
	renderer->SetRenderer(image, D3DXCOLOR(1, 1, 1, 1));

	var img_info = image->info;
	collider->SetCollider(img_info.Width / 3 * 2, img_info.Height / 3 * 2);

	m_object->fire_helper = new FireHelper();
}

void Player::Update()
{
	m_object->fire_helper->Update();

	m_transform->m_rotationZ = 90 + D3DXToDegree(atan2(mouse.y - m_position->y, mouse.x - m_position->x));

	if (GetKey('A') && m_transform->m_position.x - (1 * DELTA * move_speed) > move_range.left)
	{
		m_transform->m_position += Vector2(-1, 0) * DELTA * move_speed;
	}
	if (GetKey('D') && m_transform->m_position.x + (1 * DELTA * move_speed) < move_range.right)
	{
		m_transform->m_position += Vector2(1, 0) * DELTA * move_speed;
	}
	if (GetKey('W') && m_transform->m_position.y - (1 * DELTA * move_speed) > move_range.top)
	{
		m_transform->m_position += Vector2(0, -1) * DELTA * move_speed;
	}
	if (GetKey('S') && m_transform->m_position.y + (1 * DELTA * move_speed) < move_range.bottom)
	{
		m_transform->m_position += Vector2(0, 1) * DELTA * move_speed;
	}

	if (GetKey(VK_SPACE))
	{
		m_object->fire_helper->Fire(*m_position, 0.25f,
			*D3DXVec2Normalize(&(mouse - *m_position), &(mouse - *m_position)),
			"Player Bullet", EP_Bullet, 10, bullet_image);
	}
}

void Player::Render()
{
}

void Player::UIRender()
{
}

void Player::Release()
{
}

void Player::Invincibility()
{
	invincibility = true;
}
