#pragma once
#include "Component.h"
class RenderC : public Component
{
public:
	RenderC(Object* object);
	~RenderC();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;
};

