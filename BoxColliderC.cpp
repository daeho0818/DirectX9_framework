#include "DXUT.h"
#include "BoxColliderC.h"

BoxColliderC::BoxColliderC(Object* object) : Component(object)
{
}

BoxColliderC::~BoxColliderC()
{
}

void BoxColliderC::Init()
{
	m_width = m_height = 0;
	show_collider = false;
}

void BoxColliderC::Update()
{
}

void BoxColliderC::Render()
{
}

void BoxColliderC::UIRender()
{
}

void BoxColliderC::Release()
{
}

void BoxColliderC::SetCollider(float width, float height)
{
	m_width = width;
	m_height = height;
}

void BoxColliderC::ShowCollider(bool active)
{
	show_collider = active;
}
