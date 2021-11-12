#include "DXUT.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Init()
{
}

void ObjectManager::Update()
{
	for (var iter = m_objects.begin(); iter != m_objects.end();)
	{
		if ((*iter) != nullptr)
		{
			for (var c_iter = (*iter)->components.begin(); c_iter != (*iter)->components.end(); ++c_iter)
			{
				if (c_iter->second != nullptr)
					c_iter->second->Update();
			}
		}

		if ((*iter)->is_destroy)
		{
			SAFE_DELETE((*iter));
			iter = m_objects.erase(iter);
		}
	}
}

void ObjectManager::Render()
{
	for (var iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		for (var c_iter = (*iter)->components.begin(); c_iter != (*iter)->components.end(); ++iter)
		{
			c_iter->second->Render();
		}
	}
}

void ObjectManager::Release()
{
	for (var iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			for (var c_iter = (*iter)->components.begin(); c_iter != (*iter)->components.end(); ++c_iter)
			{
				if (c_iter->second != nullptr)
				{
					c_iter->second->Release();
					SAFE_DELETE(c_iter->second);
				}
			}
			(*iter)->components.clear();

			SAFE_DELETE((*iter));
		}
	}
	m_objects.clear();
}

Object* ObjectManager::CreateObject(string name, ObjType type, Vector2 position)
{
	Object* object = new Object(name, type, position);

	m_objects.push_back(object);

	return object;
}

list<Object*> ObjectManager::FindObject(string name)
{
	list<Object*> obj_list;

	for (var iter : m_objects)
	{
		if (iter->m_name == name)
			obj_list.push_back(iter);
	}

	return obj_list;
}

list<Object*> ObjectManager::FindObject(ObjType type)
{
	list<Object*> obj_list;

	for (var iter : m_objects)
	{
		if (iter->m_type == type)
			obj_list.push_back(iter);
	}

	return obj_list;
}