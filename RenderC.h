#pragma once
#include "Component.h"
class RenderC : public Component
{
public:
	RenderC(Object* object);
	~RenderC();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;
};

