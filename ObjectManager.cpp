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
			switch ((*iter)->m_type)
			{
			case ObjType::EPlayer:
				SAFE_DELETE(m_player);
				break;
			case ObjType::EEnemy:
				m_enemies.erase(iter);
				break;
			case ObjType::EE_Bullet:
				m_eBullets.erase(iter);
				break;
			case ObjType::EP_Bullet:
				m_pBullets.erase(iter);
				break;
			case ObjType::EItem:
				m_items.erase(iter);
			}
			SAFE_DELETE((*iter));
			iter = m_objects.erase(iter);
		}
	}

	CheckAllCollider();
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

void ObjectManager::UIRender()
{
	for (var iter = m_objects.begin(); iter != m_objects.end();)
	{
		if ((*iter) != nullptr)
		{
			for (var c_iter = (*iter)->components.begin(); c_iter != (*iter)->components.end();)
			{
				if ((*c_iter).second != nullptr)
				{
					c_iter->second->UIRender();
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

void ObjectManager::CheckAllCollider()
{
	BoxColliderC* player_collider = m_player->GetComponent<BoxColliderC>();

	for (var e_iter : m_enemies)
	{
		if (player_collider->OBBCheck(e_iter->m_transform))
		{
			player_collider->m_object->OnCollisionEnter(e_iter);
			e_iter->OnCollisionEnter(player_collider->m_object);
		}

		for (var pb_iter : m_pBullets)
		{
			if (e_iter->GetComponent<BoxColliderC>()->OBBCheck(pb_iter->m_transform))
			{
				e_iter->OnCollisionEnter(pb_iter);
				pb_iter->OnCollisionEnter(e_iter);
			}
		}
	}

	for (var eb_iter : m_eBullets)
	{
		if (player_collider->OBBCheck(eb_iter->m_transform))
		{
			player_collider->m_object->OnCollisionEnter(eb_iter);
			eb_iter->OnCollisionEnter(player_collider->m_object);
		}
	}

	for (var i_iter : m_items)
	{
		if (player_collider->OBBCheck(i_iter->m_transform))
		{
			player_collider->m_object->OnCollisionEnter(i_iter);
			i_iter->OnCollisionEnter(player_collider->m_object);
		}
	}
}
