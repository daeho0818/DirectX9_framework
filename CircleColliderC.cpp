#include "DXUT.h"
#include "CircleColliderC.h"

CircleColliderC::CircleColliderC(Object* object)
	:Component(object)
{
}

CircleColliderC::~CircleColliderC()
{
}

void CircleColliderC::Init()
{
	m_radius = 0;
	show_collider = false;
}

void CircleColliderC::Update()
{
}

void CircleColliderC::Render()
{
	// if (show_collider)
	// {
	// 	RENDER->CenterRender(IMAGE->FindImage(""), m_transform->m_position);
	// }
}

void CircleColliderC::UIRender()
{
}

void CircleColliderC::Release()
{
}

void CircleColliderC::SetCollider(float radius)
{
	m_radius = radius;
}

void CircleColliderC::ShowCollider(bool active)
{
	show_collider = active;
}
