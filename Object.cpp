#include "DXUT.h"
#include "Object.h"

Object::Object(string name, ObjType type, Vector2 position)
	:m_name(name), m_type(type)
{
	m_transform = AddComponent<TransformC>();
	m_transform->m_position = position;

	m_hp = 0;

	activeSelf = true;
	is_destroy_check = false;
	wait_for_destroy = false;
	spawn_animation = false;

	OnCollisionEnter = null;
}

Object::~Object()
{
	for (var iter : components)
	{
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	components.clear();
	SAFE_DELETE(fire_helper);
}

void Object::SpawnAnimation(Vector2 scale)
{
	D3DXVec2Lerp(&m_transform->m_localScale, &m_transform->m_localScale, &scale, 0.1f);

	if (D3DXVec2Length(&(scale - m_transform->m_localScale)) <= 0.01f)
	{
		m_transform->m_localScale = scale;
		spawn_animation = false;
	}
}

void Object::HitAnimation(D3DXCOLOR color)
{
	var renderer = GetComponent<RendererC>();
	renderer->SetColor(color);

	hit_animation = new Timer(0.1f, 0, [=]()->void
		{
			renderer->SetColor(D3DXCOLOR(1, 1, 1, 1));
			hit_animation = null;
		});
	hit_animation->TimerStart();
}