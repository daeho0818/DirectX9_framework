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
	move_range =
	{
		0,
		0,
		WINSIZEX,
		WINSIZEY
	};

	m_position = &(m_transform->m_position);
	m_transform->m_localScale = Vector2(0.5f, 0.5f);

	move_speed = 1000;
	fire_range = 0.5f;
	m_object->OnCollisionEnter = [&](Object* other)->void {};

	bullet_image = IMAGE->FindImage("Bullet_Player");

	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();

	renderer->Setting(IMAGE->FindImage("Player"), D3DXCOLOR(1, 1, 1, 1));

	m_object->fire_helper = new FireHelper();
}

void Player::Update()
{
	m_object->fire_helper->Update();

	ChkMoveRange();

	m_transform->m_rotationZ = 90 +
		D3DXToDegree(atan2(mouse.y - m_position->y, mouse.x - m_position->x));

	if (GetKey('A'))
	{
		m_transform->m_position += Vector2(-1, 0) * DELTA * move_speed;
	}
	if (GetKey('D'))
	{
		m_transform->m_position += Vector2(1, 0) * DELTA * move_speed;
	}
	if (GetKey('W'))
	{
		m_transform->m_position += Vector2(0, -1) * DELTA * move_speed;
	}
	if (GetKey('S'))
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

void Player::ChkMoveRange()
{
	if (m_position->x < move_range.left)
		m_transform->m_position.x = move_range.left;
	else if (m_position->x > move_range.right)
		m_transform->m_position.x = move_range.right;

	if (m_position->y < move_range.top)
		m_transform->m_position.y = move_range.top;
	else if (m_position->y > move_range.bottom)
		m_transform->m_position.y = move_range.bottom;
}
