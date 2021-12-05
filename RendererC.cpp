#include "DXUT.h"
#include "RendererC.h"

RendererC::RendererC(Object* object) : Component(object)
{
}

RendererC::~RendererC()
{
}

void RendererC::Init()
{
}

void RendererC::Update()
{
}

void RendererC::Render()
{
	RENDER->CenterRender(m_image, m_transform->m_position, m_transform->m_scale, D3DXToRadian(m_transform->m_rotationZ), false, m_color);
}

void RendererC::UIRender()
{
}

void RendererC::Release()
{
}

void RendererC::SetImage(Image* image)
{
	m_image = image;
}

Image* RendererC::GetImage()
{
	return m_image;
}
