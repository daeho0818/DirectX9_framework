#include "DXUT.h"
#include "Object.h"
//Object::Object(string name, ObjType type, Vector2 position)
//{
//	transform = GetComponent<TransformC>();
//}

Object::Object(string name, ObjType type, Vector2 position)
	:m_name(name), m_type(type)
{
	m_transform = AddComponent<TransformC>();
	m_transform->m_position = position;

	is_destroy = false;
	OnCollisionEnter = nullptr;
}

Object::~Object()
{
}
