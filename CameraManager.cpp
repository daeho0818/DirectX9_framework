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
	IMAGE->QuickLoad("Screen", "Public/Screen");
	screen_image = IMAGE->FindImage("Screen");

	projPos = { -WINSIZEX, WINSIZEY, 100 };
	cam_position = { 0, 0 };
	camUp = { 0, 1, 0 };

	D3DXMatrixOrthoLH(&matProj, projPos.x, projPos.y, 0, projPos.z);
}

void CameraManager::Update()
{
	if (DXUTIsKeyDown(VK_RETURN))
		MovingCamera(Vector2(WINSIZEX / 2, 0), 5);
	if (DXUTIsKeyDown(VK_BACK))
		ShakingCamera(3, 5, true);
	if (DXUTIsKeyDown(VK_SPACE))
		ZoomingCamera(0.1f, 5);

	if (camera_mode[0])
		Moving();
	if (camera_mode[1])
		Zooming();
	if (camera_mode[2])
		Shaking();
	if (camera_mode[3])
		Fading();

	D3DXMATRIXA16 m_pos, m_scale, m_rot;

	D3DXMatrixScaling(&m_scale, cam_zoom_value, cam_zoom_value, 1);
	D3DXMatrixTranslation(&m_pos, -(cam_position.x + WINSIZEX / 2), -(cam_position.y + WINSIZEY / 2), 0);
	D3DXMatrixRotationZ(&m_rot, D3DXToRadian(180));

	matView = m_pos * m_scale * m_rot;
}

void CameraManager::Render()
{
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);
	DEVICE->SetTransform(D3DTS_VIEW, &matView);

	if (camera_mode[3] && !fading_information.is_ui)
	{
		RENDER->CenterRender(screen_image, CENTER, 0.5f);
	}
}

void CameraManager::UIRender()
{
	if (camera_mode[3] && fading_information.is_ui)
	{
		RENDER->CenterRender(screen_image, CENTER);
	}
}

void CameraManager::Release()
{
}

void CameraManager::MovingCamera(Vector2 target_position, float move_speed)
{
	moving_information.target_position = target_position - CENTER;
	moving_information.move_speed = move_speed;

	shaking_information.return_position = cam_position; // 카메라 이동 시 Shake로 인한 초기화에 문제가 생길 수 있기 때문

	camera_mode[0] = true;
}

void CameraManager::ZoomingCamera(float zoom_value, float zoom_speed)
{
	zooming_information.zoom_value = zoom_value;
	zooming_information.oper_value = (zoom_value > cam_zoom_value ? 0.05f : -0.05f) * zoom_speed;

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

Vector2 CameraManager::GetPosition()
{
	return cam_position;
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

float random_x = 0;
float random_y = 0;
void CameraManager::Shaking()
{
	if (shaking_information.current_count - shaking_information.start_count >= (shaking_information.shake_time - shaking_information.shake_time / 3) * 1000) // 흔들림 감소 시작
	{
		shaking_information.shake_power -= shaking_information.shake_power / 5;
	}
	else if (shaking_information.current_count - shaking_information.start_count >= shaking_information.shake_time * 1000) // 끝
	{
		cam_position = shaking_information.return_position;
		camera_mode[2] = false;
	}

	shaking_information.current_count = GetTickCount64();

	cam_position -= Vector2(random_x, random_y);

	random_x = rand() % 10 * shaking_information.shake_power;
	random_y = rand() % 10 * shaking_information.shake_power;

	cam_position += Vector2(random_x, random_y);
}

void CameraManager::Fading()
{
}
