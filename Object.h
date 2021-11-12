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

		if (find != components.end()) return dynamic_cast<T*>(find->second);

		T* component = new T(this);
		return component;
	}

	string m_name;
	ObjType m_type;
	TransformC* m_transform;

	bool is_destroy;

private:
	map<string, Component*> components;
	function<void(Object* other)> OnCollisionEnter;

};