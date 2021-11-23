#pragma once
class CircleColliderC : public Component
{
public:
	CircleColliderC(Object* object);
	~CircleColliderC();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	// Collider 크기 설정
	void SetCollider(float radius);
	// (개발자 전용) 화면에 Collider를 보여줌
	void ShowCollider(bool active);

private:
	float m_radius;
	bool show_collider;
};

