#include "DXUT.h"
#include "Enemy1_3.h"

Enemy1_3::Enemy1_3(Object* object)
	:Component(object)
{
}

Enemy1_3::~Enemy1_3()
{
}

void Enemy1_3::Init()
{
	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();
	renderer->Setting(IMAGE->FindImage("White"), D3DXCOLOR(0, 1, 0, 1));

	m_transform->m_localScale = Vector2(0.2f, 0.2f);
}

void Enemy1_3::Update()
{
}

void Enemy1_3::Render()
{
}

void Enemy1_3::UIRender()
{
}

void Enemy1_3::Release()
{
}
