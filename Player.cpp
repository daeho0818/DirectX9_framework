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

	if (GetKeyDown(VK_SPACE))
	{
		Object* bulletObj = OBJECT->CreateObject("player_bullet", ObjType::EP_Bullet, m_object->m_transform->m_position);
		Bullet* bullet = bulletObj->AddComponent<Bullet>();
		bullet->SetBullet(Vector2(1, 0), 1, bullet_image);
	}

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