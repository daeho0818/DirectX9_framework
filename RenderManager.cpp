#include "DXUT.h"
#include "RenderManager.h"

RenderManager::RenderManager()
{
	D3DXCreateSprite(DEVICE, &m_sprite);
}

RenderManager::~RenderManager()
{
	m_sprite->Release();
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

void RenderManager::CenterRender(Image* image, Vector2 pos, float size, float rot, bool is_ui, D3DXCOLOR color)
{
	Vector2 cam_position = CAMERA->GetPosition();

	D3DXMATRIXA16 mat;
	Vector2 center = { image->info.Width / 2 * size + (is_ui ? cam_position.x : 0), image->info.Height / 2 * size + (is_ui ? cam_position.y : 0) };
	D3DXMatrixAffineTransformation2D(&mat, size, &center, rot, &(pos - center));
	m_sprite->SetTransform(&mat);
	m_sprite->Draw(image->ptr, null, null, null, color);
}
void RenderManager::CenterRender(Image* image, Vector2 pos, Vector2 scale, float rot, bool is_ui, D3DXCOLOR color)
{
	Vector2 cam_position = CAMERA->GetPosition();

	D3DXMATRIXA16 mat;
	Vector2 center = { image->info.Width / 2 * scale.x + (is_ui ? cam_position.x : 0), image->info.Height / 2 * scale.y + (is_ui ? cam_position.y : 0) };
	D3DXMatrixTransformation2D(&mat, &Vector2(0, 0), 0, &scale, &center, rot, &(pos - center));
	m_sprite->SetTransform(&mat);
	m_sprite->Draw(image->ptr, null, null, null, color);
}

void RenderManager::CropRender(Image* image, Vector2 pos, RECT& rc, float size, float rot, bool is_ui, D3DXCOLOR color)
{
	Vector2 cam_position = CAMERA->GetPosition();

	D3DXMATRIXA16 mat;
	Vector2 center = { image->info.Width / 2 * size + (is_ui ? cam_position.x : 0), image->info.Height / 2 * size + (is_ui ? cam_position.y : 0) };
	D3DXMatrixAffineTransformation2D(&mat, size, &center, rot, &(pos - center));
	m_sprite->SetTransform(&mat);
	m_sprite->Draw(image->ptr, &rc, null, null, color);
}

void RenderManager::TextRender(string str, Vector2 pos, float size, D3DXCOLOR color)
{
	Vector2 cam_position = CAMERA->GetPosition();

	D3DXMATRIXA16 mat;
	D3DXCreateFontA(DEVICE, size, 0, 10, 1, 0, DEFAULT_CHARSET, 0, 0, 0, "NanumSquareRoundOTFB", &m_font);
	D3DXMatrixTranslation(&mat, pos.x - size * (str.size() * 0.25) + cam_position.x, pos.y - size / 2 + cam_position.y, 0);
	m_sprite->SetTransform(&mat);
	m_font->DrawTextA(m_sprite, str.c_str(), str.size(), null, DT_NOCLIP, color);
	m_font->Release();
}
