#pragma once
#include "RendererC.h"
class BoxColliderC : public Component
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

	// (개발자 전용) 화면에 Collider를 보여줌
	void ShowCollider(bool active);

	bool OBBCheck(TransformC* other_transform);

private:
	bool show_collider;

	bool Dotting(Vector2 direction, TransformC* other_transform, RendererC* other_renderer);
};