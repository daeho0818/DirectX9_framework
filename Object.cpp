#include "DXUT.h"
#include "Object.h"

Object::Object(string name, ObjType type, Vector2 position)
	:m_name(name), m_type(type)
{
	m_transform = AddComponent<TransformC>();
	m_transform->m_position = position;

	activeSelf = true;
	is_destroy = false;
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
