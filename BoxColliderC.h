#pragma once
#include "RendererC.h"
class BoxColliderC : public Component
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

	// (������ ����) ȭ�鿡 Collider�� ������
	void ShowCollider(bool active);

	bool OBBCheck(TransformC* other_transform);

private:
	bool show_collider;

	bool Dotting(Vector2 direction, TransformC* other_transform, RendererC* other_renderer);
};