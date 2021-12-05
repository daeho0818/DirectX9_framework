#pragma once
#include "RendererC.h"
class BoxColliderC : Component
{
public:
	BoxColliderC(Object* object);
	~BoxColliderC();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	// Collider ũ�� ����
	void SetCollider(float width, float height);
	// (������ ����) ȭ�鿡 Collider�� ������
	void ShowCollider(bool active);

	bool OBBCheck(TransformC* other_transform);

private:
	Image* rect_image;
	RendererC* render_c;

	float m_width;
	float m_height;
	bool show_collider;

	bool Dotting(Vector2 direction, TransformC* other_transform);
};