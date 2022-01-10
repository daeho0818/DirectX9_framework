#include "DXUT.h"
#include "Cannon.h"

Cannon::Cannon(Object* object)
	: Component(object)
{
}

Cannon::~Cannon()
{
}

void Cannon::Init()
{
	m_object->m_hp = 50;
}

void Cannon::Update()
{
}

void Cannon::Render()
{
}

void Cannon::UIRender()
{
}

void Cannon::Release()
{
}

void Cannon::SetCannon(Image* image)
{
	renderer = m_object->AddComponent<RendererC>();
	renderer->SetRenderer(image, D3DXCOLOR(1, 1, 1, 1));
}

void Cannon::Rotation(Vector2 target_position)
{
	Vector2 direction = target_position - m_transform->m_position;
	D3DXVec2Normalize(&direction, &direction);
	m_transform->m_rotationZ = D3DXToDegree(atan2(direction.y, direction.x)) - 90;
}
