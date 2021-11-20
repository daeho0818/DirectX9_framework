#pragma once
class BoxColliderC : Component
{
public:
	BoxColliderC(Object* object);
	~BoxColliderC();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void SetCollider(float width, float height);
	void ShowCollider(bool active);

private:
	Image* rect_image;

	float m_width;
	float m_height;
	bool show_collider;
};