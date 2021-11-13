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
	move_speed = 5;
}

void Player::Update()
{
	if (DXUTIsKeyDown(VK_LEFT))
	{
		m_object->m_transform->m_position.x -= move_speed;
	}
	else if (DXUTIsKeyDown(VK_RIGHT))
	{
		m_object->m_transform->m_position.x += move_speed;
	}
	else if (DXUTIsKeyDown(VK_UP))
	{
		m_object->m_transform->m_position.y -= move_speed;
	}
	else if (DXUTIsKeyDown(VK_DOWN))
	{
		m_object->m_transform->m_position.y += move_speed;
	}
}

void Player::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Main_BG_Moon"), m_object->m_transform->m_position);
}

void Player::Release()
{
}

void Player::ChkMoveRange()
{
	if (m_position->x < move_range.left)
		m_object->m_transform->m_position.x = move_range.left;
	else if (m_position->x > move_range.right)
		m_object->m_transform->m_position.x = m_position->x > move_range.right;
	
	if (m_position->y < move_range.top)
		m_object->m_transform->m_position.y = move_range.top;
	else if (m_position->y > move_range.bottom)
		m_object->m_transform->m_position.y = move_range.bottom;
}