#pragma once
#include "Singleton.h"
#include "Component.h"
#include "Image.h"
class RenderManager : public Singleton<RenderManager>
{
public:
	RenderManager();
	~RenderManager();

	void Begin();
	void End();
	void Reset();
	void Lost();

	void CenterRender(Image* image, Vector2 pos, float size, D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1));
	void CropRender(Image* image, Vector2 pos, RECT& rc, float size, D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1));
	void PrintText(string str, Vector2 pos, float size, D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1));

private:
	LPD3DXSPRITE m_sprite;
	LPD3DXFONT m_font;
};
