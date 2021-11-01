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

	void MovingCamera(Vector2 move_position, float move_speed);
	void ZoomingCamera(float zoom_value, float zoom_speed);
	void ShakingCamera(float shake_power, float shake_time, bool is_smooth_end);
	void FadeCamera(float fade_time, bool fade_in);

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