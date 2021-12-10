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
	if (m_image)
	{
		RENDER->CenterRender(m_image, m_transform->m_position, 
			m_transform->m_localScale, D3DXToRadian(m_transform->m_rotationZ),
			false, m_color);
	}
}

void RendererC::UIRender()
{
}

void RendererC::Release()
{
}

void RendererC::Setting(Image* image, D3DXCOLOR color)
{
	m_image = image;
	m_color = color;
}

void RendererC::SetImage(Image* image)
{
	m_image = image;
}

Image* RendererC::GetImage()
{
	return m_image;
}

void RendererC::SetColor(D3DXCOLOR color)
{
	m_color;
}

D3DXCOLOR RendererC::GetColor()
{
	return m_color;
}
