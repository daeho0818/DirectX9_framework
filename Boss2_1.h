#pragma once
#include "Cannon.h"
class Boss2_1 : public Component
{
public:
	Boss2_1(Object* object);
	~Boss2_1();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	Cannon* cannons[4];
};

