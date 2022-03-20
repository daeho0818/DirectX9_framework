#pragma once
#include "Component.h"
class RendererC : public Component
{
public:
	RendererC(Object* object);
	~RendererC();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void SetRenderer(Image* image, D3DXCOLOR color, bool is_ui = false);

	void SetImage(Image* image);
	Image* GetImage();
	void SetColor(D3DXCOLOR color);
	D3DXCOLOR GetColor();

private:
	Image* m_image = nullptr;
	D3DXCOLOR m_color;

	bool is_ui;

};

