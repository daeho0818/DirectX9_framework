#pragma once
class Object;
class TransformC;
class Component
{
public:
	Component(Object* object) : m_object(object) { enabled = true; }
	virtual ~Component() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void UIRender() = 0;
	virtual void Release() = 0;

	Object* m_object = nullptr;
	TransformC* m_transform;

	bool  enabled;

};
