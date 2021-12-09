#pragma once
#include "Component.h"
class RendererC : public Component
{
public:
	RendererC(Object* object);
	~RendererC();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void Setting(Image* image, D3DXCOLOR color);

	void SetImage(Image* image);
	Image* GetImage();
	void SetColor(D3DXCOLOR color);
	D3DXCOLOR GetColor();

private:
	Image* m_image = null;
	D3DXCOLOR m_color;

};

