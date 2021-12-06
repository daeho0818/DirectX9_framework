#pragma once
#include "BoxColliderC.h"
#include "Object.h"

class ObjectManager : public Singleton<ObjectManager>
{
	friend class Object;
public:
	ObjectManager();
	~ObjectManager();

	void Init();
	void Update();
	void Render();
	void UIRender();
	void Release();

	Object* CreateObject(string name, ObjType type, Vector2 position);
	list<Object*> FindObject(string name);
	list<Object*> FindObject(ObjType type);
	void DestroyAllObject();
	void CheckAllCollider();

private:
	list<Object*> m_objects;

	Object* m_player;
	list<Object*> m_eBullets;
	list<Object*> m_pBullets;
	list<Object*> m_enemies;
	list<Object*> m_items;

};
#define OBJECT ObjectManager::Instance()