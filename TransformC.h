#pragma once
class TransformC : public Component
{
	friend class Object;
public :
	TransformC(Object* object);
	~TransformC();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	template <typename T>
	T* GetComponent()
	{
		auto find = m_object->components.find(typeid(T).name());

		if (find != m_object->components.end()) return dynamic_cast<T*>(find->second);
		return nullptr;
	}

	template <typename T>
	T* AddComponent()
	{
		auto find = m_object->components.find(typeid(T).name());

		if (find != m_object->components.end()) return dynamic_cast<T*>(find->second);

		T* t_component = new T(this);
		Component* component = dynamic_cast<Component*>(t_component);
		m_object->components.insert(make_pair(typeid(T).name(), component));
		component->m_transform = m_transform;
		component->Init();
		return t_component;
	}

	Vector2 m_position;
	Vector2 right;
	Vector2 left;
	Vector2 up;
	Vector2 down;

	float m_scale;
	float m_rotationZ;
};

