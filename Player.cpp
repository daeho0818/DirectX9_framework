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
	move_speed = 15;
	fire_range = 0.5f;
	m_object->OnCollisionEnter = [&](Object* other)->void {};

	IMAGE->QuickLoad("bullet_player", "Object/Bullet/bullet_player");
	bullet_image = IMAGE->FindImage("bullet_player");

	collider = m_object->AddComponent<BoxColliderC>();
	render = m_object->AddComponent<RendererC>();

	render->SetImage(IMAGE->FindImage("Main_BG_Moon"));
}

void Player::Update()
{
	if (GetKey(VK_LEFT))
	{
		m_transform->m_position += m_transform->left * move_speed;
	}
	else if (GetKey(VK_RIGHT))
	{
		m_transform->m_position += m_transform->right * move_speed;
	}
	else if (GetKey(VK_UP))
	{
		m_transform->m_position += m_transform->up * move_speed;
	}
	else if (GetKey(VK_DOWN))
	{
		m_transform->m_position += m_transform->down * move_speed;
	}

	if (GetKey(VK_SPACE)) Fire();
	current_fire_count = GetTickCount64();

	ChkMoveRange();

	if (is_wasd)
	{
		if (GetKey(VK_F1))
			m_transform->m_rotationZ += 5;
		else if (GetKey(VK_F2))
			m_transform->m_rotationZ -= 5;
	}
}

void Player::Render()
{
}

void Player::UIRender()
{
	if (collider->OBBCheck(other_player->m_transform))
	{
		RENDER->TextRender("Ãæµ¹ÇÔ!", CENTER, 500);
	}
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

void Player::Fire()
{
	if (current_fire_count - first_fire_count > fire_range * 1000)
	{
		Object* bulletObj = OBJECT->CreateObject("player_bullet", ObjType::EP_Bullet, (*m_position));
		Bullet* bullet = bulletObj->AddComponent<Bullet>();
		Vector2& dir = INPUT->GetMousePosition() - (*m_position);
		bullet->SetBullet(*D3DXVec2Normalize(&dir, &dir), 1, bullet_image);

		first_fire_count = GetTickCount64();
	}
}
