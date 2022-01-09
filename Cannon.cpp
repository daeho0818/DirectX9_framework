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
}
