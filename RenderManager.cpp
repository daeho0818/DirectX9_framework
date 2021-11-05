#include "DXUT.h"
#include "RenderManager.h"

RenderManager::RenderManager()
{
	D3DXCreateSprite(DEVICE, &m_sprite);
}

RenderManager::~RenderManager()
{
	m_sprite->Release();
	SAFE_RELEASE(m_font);
}

void RenderManager::Begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void RenderManager::End()
{
	m_sprite->End();
}

void RenderManager::Reset()
{
	m_sprite->OnResetDevice();
}

void RenderManager::Lost()
{
	m_sprite->OnLostDevice();
}

void RenderManager::CenterRender(Image* image, Vector2 pos, float size, D3DXCOLOR color)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixAffineTransformation2D(&mat, size, nullptr, 0, &Vector2(pos.x - (image->info.Width / 2) * size, pos.y - (image->info.Height / 2) * size));
	m_sprite->SetTransform(&mat);
	m_sprite->Draw(image->ptr, nullptr, nullptr, nullptr, color);
}

void RenderManager::CropRender(Image* image, Vector2 pos, RECT& rc, float size, D3DXCOLOR color)
{
	D3DXMATRIXA16 mat;
	Vector2 targetPos = { pos.x - image->info.Width / 2 * size, pos.y - image->info.Height / 2 * size };
	D3DXMatrixAffineTransformation2D(&mat, size, nullptr, 0, &targetPos);
	m_sprite->SetTransform(&mat);
	m_sprite->Draw(image->ptr, &rc, nullptr, nullptr, color);
}

void RenderManager::TextRender(string str, Vector2 pos, float size, D3DXCOLOR color)
{
	D3DXMATRIXA16 mat;
	D3DXCreateFontA(DEVICE, 1, size, 0, 10, 1, 0, DEFAULT_CHARSET, 0, 0, "나눔스퀘어 AC", &m_font);
	m_sprite->SetTransform(&mat);
	m_font->DrawTextA(m_sprite, str.c_str(), str.size(), nullptr, DT_NOCLIP, color);
	m_font->Release();
}
