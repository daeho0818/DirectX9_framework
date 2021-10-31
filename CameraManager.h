#pragma once
#include "Singleton.h"
class CameraManager : public Singleton<CameraManager>
{
public:
	CameraManager();
	~CameraManager();

	void Init();
	void Update();
	void Release();

	void MovingCamera(Vector2 position, float move_speed);
	void ZoomingCamera();
	void ShakingCamera();
	void FadeCamera();

private:
	struct VertexType
	{
		Vector3 m_position;
		Vector2 m_uv;
		static constexpr DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	};

	Vector3 projPos;
	Vector3 camUp;
	Vector2 camPos;
	Vector2 m_targetPos;

	D3DXMATRIXA16 matProj;
	D3DXMATRIX matView;

	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DINDEXBUFFER9 m_ib;
};
#define CAMERA CameraManager::Instance()