#include "DXUT.h"
#include "Button.h"

Button::Button(Object* object) : Component(object)
{
}

Button::~Button()
{
}

void Button::Init()
{
}

void Button::Update()
{
}

void Button::Render()
{
}

void Button::UIRender()
{
}

void Button::Release()
{
}

void Button::SetButton(Vector2 position, RECT size, Image* images[3])
{
	m_transform->m_position = position;
	m_size = size;
	m_image = images[0];
	m_image_up = images[1];
	m_image_press = images[2];
}

void Button::SetOnClickListener(function<void()> func)
{
	onClickListener = func;
}
