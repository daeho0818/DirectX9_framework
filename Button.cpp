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

void Button::SetButton(Vector2 position, RECT size)
{
	m_transform->m_position = position;
	m_size = size;
}

void Button::SetOnClickListener(function<void()> func)
{
	onClickListener = func;
}
