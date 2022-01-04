#pragma once
#include "Component.h"
#include "TransformC.h"
#include "FireHelper.h"
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
		is_destroy_check = m_transform->m_position.x > WINSIZEX + 300 ||
			m_transform->m_position.x < -300 ||
			m_transform->m_position.y > WINSIZEY + 300 ||
			m_transform->m_position.y < -300;
	}

	void SetActive(bool active) { activeSelf = active; }
	bool ActiveSelf() { return activeSelf; };
	void SpawnAnimation(Vector2 scale);
	void HitAnimation(D3DXCOLOR color);

	string m_name;
	ObjType m_type;
	TransformC* m_transform = nullptr;

	function<void(Object* other)> OnCollisionEnter = nullptr;
	function<void()> OnDestroy = nullptr;

	FireHelper* fire_helper = nullptr;

	int m_hp;

	bool is_destroy_check;
	bool wait_for_destroy;
	bool spawn_animation;

private:
	map<string, Component*> components;

	Timer* hit_animation = nullptr;

	bool activeSelf;

};
