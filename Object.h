#pragma once
#include "Component.h"
#include "TransformC.h"
class Object
{
	friend class TransformC;
	friend class ObjectManager;
public:
	Object(string name, ObjType type, Vector2 position);
	~Object();

	template <typename T>
	T* GetComponent()
	{
		auto find = components.find(typeid(T).name());

		if (find != components.end()) return dynamic_cast<T*>(find->second);
		return null;
	}

	template <typename T>
	T* AddComponent()
	{
		auto find = components.find(typeid(T).name());

		if (find != components.end()) return dynamic_cast<T*>(find->second);

		T* t_component = new T(this);
		Component* component = (Component*)(t_component);
		component->m_transform = m_transform;
		component->Init();
		components.insert(make_pair(typeid(T).name(), component));
		return t_component;
	}

	void CheckOut()
	{
		is_destroy = m_transform->m_position.x > WINSIZEX + 200 || m_transform->m_position.x < -200 || m_transform->m_position.y > WINSIZEY + 200 || m_transform->m_position.y < -200;
	}

	void SetActive(bool active) { activeSelf = active; }
	bool ActiveSelf() { return activeSelf; };

	string m_name;
	ObjType m_type;
	TransformC* m_transform = nullptr;
	function<void(Object* other)> OnCollisionEnter = nullptr;

	bool is_destroy;

private:
	map<string, Component*> components;

	bool activeSelf;

};
