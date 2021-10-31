#pragma once
#include "Component.h"
class Object
{
	Object();
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

private:
	map<string, Component*> components;

};