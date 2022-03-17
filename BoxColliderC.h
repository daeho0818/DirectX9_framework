#pragma once
#include "RendererC.h"
class BoxColliderC : public Component
{
	friend class ObjectManager;
public:
	BoxColliderC(Object* object);
	~BoxColliderC();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	// (������ ����) ȭ�鿡 Collider�� ������
	void ShowCollider(bool active);
	void SetCollider(RendererC* renderer);
	void SetCollider(float width, float height);

	bool OBBCheck(TransformC* other_transform);

private:
	bool show_collider;
	bool is_set;

	float m_width;
	float m_height;

	bool Dotting(Vector2 direction, BoxColliderC* other_collider);
};