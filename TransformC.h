#pragma once
class TransformC : public Component
{
public :
	TransformC(Object* object);
	~TransformC();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	Vector2 m_position;
	Vector2 right;
	Vector2 left;
	Vector2 up;
	Vector2 down;

	float m_scale;
	float m_rotationZ;
};

