#pragma once
#include "Component.h"
#include "TransformC.h"
class Object
{
	friend class ObjectManager;
public:
	Object(string name, ObjType type, Vector2 position);
	virtual ~Object();

	template <typename T>
	T* GetComponent()
	{
		auto find = components.find(typeid(T).name());
		
		if (find != components.end()) return find->second;
		return nullptr;
	}

	template <typename T>
	T* AddComponent()
	{
		auto find = components.find(typeid(T).name());

		if (find != components.end()) return find->second;

		Component* component;
		return dynamic_cast<T*>(component);
	}

	string m_name;
	ObjType m_type;
	TransformC* m_transform;

private:
	map<string, Component*> components;

};