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
		if (!(*iter)->is_destroy)
		{
			for (var c_iter = (*iter)->components.begin(); c_iter != (*iter)->components.end();)
			{
				c_iter->second->Update();
				++c_iter;
			}
			++iter;
		}
		else 
		{
			SAFE_DELETE((*iter));
			iter = m_objects.erase(iter);
		}
	}
}

void ObjectManager::Render()
{
	for (var iter = m_objects.begin(); iter != m_objects.end();)
	{
		if ((*iter) != nullptr)
		{
			for (var c_iter = (*iter)->components.begin(); c_iter != (*iter)->components.end();)
			{
				if ((*c_iter).second != nullptr)
				{
					c_iter->second->Render();
					++c_iter;
				}
			}
			++iter;
		}
	}
}

void ObjectManager::Release()
{
	DestroyAllObject();
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

void ObjectManager::DestroyAllObject()
{
	for (var iter = m_objects.begin(); iter != m_objects.end();)
	{
		for (var c_iter = (*iter)->components.begin(); c_iter != (*iter)->components.end();)
		{
			if (c_iter->second != nullptr)
			{
				c_iter->second->Release();
				SAFE_DELETE(c_iter->second);
				c_iter = (*iter)->components.erase(c_iter);
			}
			else ++c_iter;
		}
		SAFE_DELETE((*iter));
		iter = m_objects.erase(iter);
	}
}
