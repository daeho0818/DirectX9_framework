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

	m_position = &(m_object->m_transform->m_position);
	move_speed = 15;
	fire_range = 0.5f;

	IMAGE->QuickLoad("bullet_player", "Object/Bullet/bullet_player");
	bullet_image = IMAGE->FindImage("bullet_player");
}

void Player::Update()
{
	if (GetKey(VK_LEFT))
	{
		m_object->m_transform->m_position.x -= move_speed;
	}
	else if (GetKey(VK_RIGHT))
	{
		m_object->m_transform->m_position.x += move_speed;
	}
	else if (GetKey(VK_UP))
	{
		m_object->m_transform->m_position.y -= move_speed;
	}
	else if (GetKey(VK_DOWN))
	{
		m_object->m_transform->m_position.y += move_speed;
	}

	if (GetKey(VK_SPACE)) Fire();
	current_fire_count = GetTickCount64();

	ChkMoveRange();
}

void Player::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Main_BG_Moon"), m_object->m_transform->m_position);
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
		m_object->m_transform->m_position.x = move_range.left;
	else if (m_position->x > move_range.right)
		m_object->m_transform->m_position.x = move_range.right;

	if (m_position->y < move_range.top)
		m_object->m_transform->m_position.y = move_range.top;
	else if (m_position->y > move_range.bottom)
		m_object->m_transform->m_position.y = move_range.bottom;
}

void Player::Fire()
{
	if (current_fire_count - first_fire_count > fire_range * 1000)
	{
		Object* bulletObj = OBJECT->CreateObject("player_bullet", ObjType::EP_Bullet, m_object->m_transform->m_position);
		Bullet* bullet = bulletObj->AddComponent<Bullet>();
		Vector2& dir = INPUT->GetMousePosition() - m_object->m_transform->m_position;
		bullet->SetBullet(*D3DXVec2Normalize(&dir, &dir), 1, bullet_image);

		first_fire_count = GetTickCount64();
	}
}
