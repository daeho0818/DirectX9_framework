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
	move_speed = 1000;
	fire_range = 0.5f;
	m_object->OnCollisionEnter = [&](Object* other)->void {};

	bullet_image = IMAGE->FindImage("bullet_player");

	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();

	renderer->Setting(IMAGE->FindImage("White"), D3DXCOLOR(1, 1, 1, 1));

	bullet_pool = new BulletPool<Bullet>("Player Bullet", ObjType::EP_Bullet, fire_range,
		bullet_image, D3DXCOLOR(1, 1, 1, 1));
}

void Player::Update()
{
	ChkMoveRange();

	bullet_pool->Update();

	if (GetKey('A'))
	{
		m_transform->m_position += m_transform->left * DELTA * move_speed;
	}
	else if (GetKey('D'))
	{
		m_transform->m_position += m_transform->right * DELTA * move_speed;
	}
	else if (GetKey('W'))
	{
		m_transform->m_position += m_transform->up * DELTA * move_speed;
	}
	else if (GetKey('S'))
	{
		m_transform->m_position += m_transform->down * DELTA * move_speed;
	}

	if (GetKey(VK_SPACE)) Fire();
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

void Player::Fire()
{
	Bullet* bullet = bullet_pool->GetBullet(m_transform->m_position);
	if (bullet)
	{
		Vector2 dir = INPUT->GetMousePosition() - (*m_position);
		bullet->SetBullet(*D3DXVec2Normalize(&dir, &dir), 1, bullet_image);
	}
}
