#include "DXUT.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::Init()
{
	DEVICE->CreateVertexBuffer(sizeof(VertexType) * 4, D3DUSAGE_WRITEONLY, VertexType::FVF, D3DPOOL_DEFAULT, &m_vb, NULL);
	VertexType* vertices = nullptr;
	m_vb->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].m_position = { -0.5, 0.5, 0 };
	vertices[1].m_position = { 0.5, 0.5, 0 };
	vertices[2].m_position = { -0.5, -0.5, 0 };
	vertices[3].m_position = { 0.5, -0.5, 0 };

	vertices[0].m_uv = { 0, 0 };
	vertices[1].m_uv = { 1, 0 };
	vertices[2].m_uv = { 0, 1 };
	vertices[3].m_uv = { 1, 1 };
	m_vb->Unlock();

	projPos = { -WINSIZEX, WINSIZEY, 100 };
	cam_position = { 0, 0 };
	camUp = { 0, 1, 0 };

	DEVICE->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_ib, NULL);
	WORD idx[] = { 1, 2, 0, 1, 3, 2 };
	void* indices = NULL;
	m_ib->Lock(0, 0, &indices, 0);
	memcpy(indices, idx, sizeof(WORD) * 6);
	m_ib->Unlock();

	DEVICE->SetStreamSource(0, m_vb, 0, sizeof(VertexType));
	DEVICE->SetFVF(VertexType::FVF);
	DEVICE->SetIndices(m_ib);

	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	projPos = { -WINSIZEX * cam_zoom_value, WINSIZEY * cam_zoom_value, 100 };

	IMAGE->QuickLoad("Screen", "Public/Screen");
	screen_image = IMAGE->FindImage("Screen");
}

void CameraManager::Update()
{
	D3DXMatrixOrthoLH(&matProj, projPos.x, projPos.y, 0, projPos.z);
	D3DXMatrixLookAtLH(&matView, &Vector3(cam_position.x, cam_position.y, 1), &Vector3(cam_position.x, cam_position.y, 0), &camUp);
}

void CameraManager::Render()
{
}

void CameraManager::UIRender()
{
}

void CameraManager::Release()
{
}

void CameraManager::MovingCamera(Vector2 target_position, float move_speed)
{
	moving_information.target_position = target_position;
	moving_information.move_speed = move_speed;

	shaking_information.return_position = cam_position; // 카메라 이동 시 Shake로 인한 초기화에 문제가 생길 수 있기 때문

	camera_mode[0] = true;
}

void CameraManager::ZoomingCamera(float zoom_value, float zoom_speed)
{
	zooming_information.zoom_value = zoom_value;
	zooming_information.oper_value = (zoom_value > cam_zoom_value ? 0.1f : -0.1f) * zoom_speed;

	camera_mode[1] = true;
}

void CameraManager::ShakingCamera(float shake_power, float shake_time, bool is_smooth_end)
{
	shaking_information.shake_power = shake_power;
	shaking_information.shake_time = shake_time;
	shaking_information.is_smooth_end = is_smooth_end;

	shaking_information.return_position = cam_position;

	shaking_information.start_count = shaking_information.current_count = GetTickCount64();

	camera_mode[2] = true;
}

void CameraManager::FadingScreen(float target_alpha, float fade_speed, bool fade_in, bool is_ui)
{
	fading_information.target_alpha = target_alpha;
	fading_information.fading_value = (fade_in ? 0.05f : -0.05f) * fade_speed;
	fading_information.fade_in = fade_in;
	fading_information.is_ui = is_ui;

	camera_mode[3] = true;
}

void CameraManager::Moving()
{
	if (moving_information.target_position - cam_position <= Vector2(0.01f, 0.01f))
	{
		cam_position = moving_information.target_position;
		camera_mode[0] = false;
	}
	D3DXVec2Lerp(&cam_position, &cam_position, &(moving_information.target_position), DELTA * moving_information.move_speed);
}

void CameraManager::Zooming()
{
	if (abs(zooming_information.zoom_value - cam_zoom_value) <= 0.01f)
	{
		cam_zoom_value = zooming_information.zoom_value;
		camera_mode[1] = false;
	}

	cam_zoom_value += zooming_information.oper_value;
}

void CameraManager::Shaking()
{
	if (shaking_information.current_count - shaking_information.start_count >= (shaking_information.shake_time - 2) * 1000) // 흔들림 감소 시작
	{
		shaking_information.shake_power -= shaking_information.shake_power / 5;
	}
	else if (shaking_information.current_count - shaking_information.start_count >= shaking_information.shake_time * 1000) // 끝
	{
		cam_position = shaking_information.return_position;
		camera_mode[2] = false;
	}

	cam_position += Vector2(rand() % 10 * shaking_information.shake_power, rand() % 10 * shaking_information.shake_power);
}

void CameraManager::Fading()
{
}
