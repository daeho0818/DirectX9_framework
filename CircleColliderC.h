#pragma once
class CircleColliderC : public Component
{
public:
	CircleColliderC(Object* object);
	~CircleColliderC();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	// Collider ũ�� ����
	void SetCollider(float radius);
	// (������ ����) ȭ�鿡 Collider�� ������
	void ShowCollider(bool active);

private:
	float m_radius;
	bool show_collider;
};

