#pragma once
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
	void Release();

	Object* CreateObject(string name, ObjType type, Vector2 position);
	list<Object*> FindObject(string name);
	list<Object*> FindObject(ObjType type);
	void DestroyAllObject();

private:
	list<Object*> m_objects;

};
#define OBJECT ObjectManager::Instance()