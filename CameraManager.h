#pragma once
#include "Singleton.h"
class CameraManager : public Singleton<CameraManager>
{
public:
	CameraManager();
	~CameraManager();

	void Init();
	void Update();
	void Render();
	void UIRender();
	void Release();

	void MovingCamera(Vector2 target_position, float move_speed);
	void ZoomingCamera(float zoom_value, float zoom_speed);
	void ShakingCamera(float shake_power, float shake_time, bool is_smooth_end);
	void FadingScreen(float fade_speed, bool fade_in, bool is_ui);

	bool IsAction(int index);
	void StopAction(int index);

	Vector2 GetPosition();

private:
	struct VertexType
	{
		Vector3 m_position;
		Vector2 m_uv;
		static constexpr DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	};

	Vector3 projPos;
	Vector3 camUp;
	Vector2 cam_position;

	D3DXMATRIXA16 matProj;
	D3DXMATRIX matView;

	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DINDEXBUFFER9 m_ib;

	// use index | 0 : moving mode, 1 : zooming mode, 2 : shaking mode, 3 : fading mode
	bool camera_mode[4] =
	{
		false, // moving mode
		false, // zooming mode
		false, // shaking mode
		false // fading mode
	};

	struct MovingInformation
	{
	public:
		Vector2 target_position;
		float move_speed;
	};
	struct ZoomingInformation
	{
	public:
		float zoom_value;
		float oper_value;
	};
	float cam_zoom_value = 1;
	struct ShakingInformation
	{
	public:
		float shake_power;
		float shake_time;
		bool is_smooth_end;
		Vector2 return_position; // 카메라를 흔드는 과정에서 기존 위치에서 벗어난 것을 되돌려놓기 위한 변수

		float current_count;
	};
	struct FadingInformation
	{
	public:
		float target_alpha;
		float fading_value;
		bool is_ui;
	};
	float screen_fade_alpha;
	float ui_screen_fade_alpha;

	MovingInformation moving_information;
	ZoomingInformation zooming_information;
	ShakingInformation shaking_information;
	FadingInformation fading_information;

	Image* screen_image = null;

	void Moving();
	void Zooming();
	void Shaking();
	void Fading();
};
#define CAMERA CameraManager::Instance()