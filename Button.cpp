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
	if (m_image)
	{
		if (INPUT->IsMouseClick(this))
		{
			if (onClickListener != null)
				onClickListener();
		}
		else if (INPUT->IsMouseOver(this))
		{
			D3DXVec2Lerp(&m_transform->m_localScale, &m_transform->m_localScale, &Vector2(1.2f, 1.2f), 0.1f);
		}
		else if (INPUT->IsMousePressed(this))
		{
			D3DXVec2Lerp(&m_transform->m_localScale, &m_transform->m_localScale, &Vector2(0.8f, 0.8f), 0.1f);
		}
		else
		{
			D3DXVec2Lerp(&m_transform->m_localScale, &m_transform->m_localScale, &Vector2(1.0f, 1.0f), 0.1f);
		}
	}
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

void Button::SetButton(Image* image)
{
	m_image = image;

	m_size =
	{
		(LONG)(m_transform->m_position.x - image->info.Width / 2),
		(LONG)(m_transform->m_position.y - image->info.Height / 2),
		(LONG)(m_transform->m_position.x + image->info.Width / 2),
		(LONG)(m_transform->m_position.y + image->info.Height / 2)
	};

	render = m_object->AddComponent<RendererC>();
	render->SetRenderer(m_image, D3DXCOLOR(1, 1, 1, 1), true);
}

void Button::SetOnClickListener(function<void()> func)
{
	onClickListener = func;
}
