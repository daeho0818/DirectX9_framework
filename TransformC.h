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
		return m_object->GetComponent<T>();
	}

	template <typename T>
	T* AddComponent()
	{
		return m_object->AddComponent<T>();
	}

	void Translate(Vector2 translation);

	Vector2 m_position;
	Vector2 right;
	Vector2 left;
	Vector2 up;
	Vector2 down;

	Vector2 m_localScale;

	float m_rotationZ;
};

