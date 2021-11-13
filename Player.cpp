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
}

void Player::Update()
{
	if (DXUTIsKeyDown(VK_LEFT))
	{
		m_object->m_transform->m_position.x -= 5;
	}
	else if (DXUTIsKeyDown(VK_RIGHT))
	{
		m_object->m_transform->m_position.x += 5;
	}
	else if (DXUTIsKeyDown(VK_UP))
	{
		m_object->m_transform->m_position.y -= 5;
	}
	else if (DXUTIsKeyDown(VK_DOWN))
	{
		m_object->m_transform->m_position.y += 5;
	}
}

void Player::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Main_BG_Cloud"), CENTER);
}

void Player::Release()
{
}

