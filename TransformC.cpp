#include "DXUT.h"
#include "TransformC.h"

TransformC::TransformC(Object* object) : Component(object)
{
	m_localScale = Vector2(1, 1);
	m_rotationZ = 0;
}

TransformC::~TransformC()
{
}

void TransformC::Init()
{
}

void TransformC::Update()
{
	left = Vector2(-cos(D3DXToRadian((int)m_rotationZ)), -sin(D3DXToRadian((int)m_rotationZ)));
	right = Vector2(cos(D3DXToRadian((int)m_rotationZ)), sin(D3DXToRadian((int)m_rotationZ)));
	up = Vector2(sin(D3DXToRadian((int)m_rotationZ)), -cos(D3DXToRadian((int)m_rotationZ)));
	down = Vector2(-sin(D3DXToRadian((int)m_rotationZ)), cos(D3DXToRadian((int)m_rotationZ)));
}

void TransformC::Render()
{
}

void TransformC::UIRender()
{
}

void TransformC::Release()
{
}

void TransformC::Translate(Vector2 translation)
{
	m_position += translation;
}
