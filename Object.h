#pragma once
#include "Component.h"
#include "TransformC.h"
class Object
{
	friend class TransformC;
	friend class ObjectManager;
public:
	Object(string name, ObjType type, Vector2 position);
	virtual ~Object();

	template <typename T>
	T* GetComponent()
	{
		auto find = components.find(typeid(T).name());
		
		if (find != components.end()) return dynamic_cast<T*>(find->second);
		return nullptr;
	}

	template <typename T>
	T* AddComponent()
	{
		auto find = components.find(typeid(T).name());

		if (find != components.end()) return dynamic_cast<T*>(find->second);

		T* t_component = new T(this);
		Component* component = dynamic_cast<Component*>(t_component);
		components.insert(make_pair(typeid(T).name(), component));
		component->m_transform = m_transform;
		component->Init();
		return t_component;
	}

	string m_name;
	ObjType m_type;
	TransformC* m_transform;
	function<void(Object* other)> OnCollisionEnter;

	bool is_destroy;

private:
	map<string, Component*> components;

};
