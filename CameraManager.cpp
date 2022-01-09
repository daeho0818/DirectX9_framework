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

	screen_fade_alpha = ui_screen_fade_alpha = 0;
}

void CameraManager::Update()
{
	if (camera_mode[0])
		Moving();
	if (camera_mode[1])
		Zooming();
	if (camera_mode[2])
		Shaking();
	if (camera_mode[3])
		Fading();

	if (GetKey(VK_LEFT))
		cam_position += Vector2(1, 0);
	if(GetKey(VK_RIGHT))
		cam_position -= Vector2(1, 0);
	if(GetKey(VK_UP))
		cam_position -= Vector2(0, 1);
	if(GetKey(VK_DOWN))
		cam_position += Vector2(0, 1);

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

	RENDER->CenterRender(screen_image, CENTER, 1, 0, fading_information.is_ui, D3DXCOLOR(0, 0, 0, screen_fade_alpha));
}

void CameraManager::UIRender()
{
	RENDER->CenterRender(screen_image, CENTER, 1, 0, fading_information.is_ui, D3DXCOLOR(0, 0, 0, ui_screen_fade_alpha));
}

void CameraManager::Release()
{
}

void CameraManager::MovingCamera(Vector2 target_position, float move_speed)
{
	moving_information.target_position = target_position - CENTER;
	moving_information.move_speed = move_speed;

	// 카메라 이동 시 Shake로 인한 초기화에 문제가 생길 수 있기 때문
	shaking_information.return_position = target_position - CENTER;

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

	shaking_information.current_count = 0;

	shaking_information.return_position = cam_position;

	camera_mode[2] = true;
}

void CameraManager::FadingScreen(float fade_speed, bool fade_in, bool is_ui)
{
	fading_information.target_alpha = fade_in ? 0 : 1;

	if (is_ui)
		ui_screen_fade_alpha = 1 - fading_information.target_alpha;
	else
		screen_fade_alpha = 1 - fading_information.target_alpha;

	fading_information.fading_value = (fade_in ? -0.005f : 0.005f) * fade_speed;
	fading_information.is_ui = is_ui;

	camera_mode[3] = true;
}

bool CameraManager::IsAction(int index) { return camera_mode[index]; };

void CameraManager::StopAction(int index)
{
	camera_mode[index] = false;

	switch (index)
	{
	case 0:
		camera_mode[0] = false;
		break;
	case 1:
		camera_mode[1] = false;
		break;
	case 2:
		shaking_information.current_count = 0;
		camera_mode[2] = false;
		break;
	case 3:
		if (fading_information.is_ui)
		{
			ui_screen_fade_alpha = fading_information.target_alpha;
			camera_mode[3] = false;
		}
		else
		{
			screen_fade_alpha = fading_information.target_alpha;
			camera_mode[3] = false;
		}
		break;
	}
}


Vector2 CameraManager::GetPosition()
{
	return cam_position;
}

float CameraManager::GetZoomValue()
{
	return cam_zoom_value;
}

void CameraManager::Moving()
{
	if (moving_information.target_position - cam_position <= Vector2(0.01f, 0.01f))
	{
		cam_position = moving_information.target_position;
		camera_mode[0] = false;

		return;
	}

	D3DXVec2Lerp(&cam_position, &cam_position, &(moving_information.target_position), DELTA * moving_information.move_speed);
}

void CameraManager::Zooming()
{
	if (abs(zooming_information.zoom_value - cam_zoom_value) <= 0.01f)
	{
		cam_zoom_value = zooming_information.zoom_value;
		camera_mode[1] = false;

		return;
	}

	cam_zoom_value += zooming_information.oper_value;
}

float random_x = 0;
float random_y = 0;
void CameraManager::Shaking()
{
	if (shaking_information.current_count >= shaking_information.shake_time) // 끝
	{
		cam_position = shaking_information.return_position;
		shaking_information.current_count = 0;
		camera_mode[2] = false;

		return;
	}
	if (shaking_information.is_smooth_end)
		shaking_information.shake_power -=
		shaking_information.shake_power / 50;


	shaking_information.current_count += DELTA;

	cam_position -= Vector2(random_x, random_y);

	random_x = rand() % 10 * shaking_information.shake_power;
	random_y = rand() % 10 * shaking_information.shake_power;

	if ((int)random_x % 2 == 0) random_x *= -1;
	if ((int)random_y % 2 == 1) random_y *= -1;

	cam_position += Vector2(random_x, random_y);
}

void CameraManager::Fading()
{
	if (fading_information.is_ui)
	{
		if (abs(fading_information.target_alpha - ui_screen_fade_alpha) <= 0.05f)
		{
			ui_screen_fade_alpha = fading_information.target_alpha;
			camera_mode[3] = false;

			return;
		}
	}
	else
	{
		if (abs(fading_information.target_alpha - screen_fade_alpha) <= 0.05f)
		{
			screen_fade_alpha = fading_information.target_alpha;
			camera_mode[3] = false;

			return;
		}
	}


	if (fading_information.is_ui)
		ui_screen_fade_alpha += fading_information.fading_value;
	else
		screen_fade_alpha += fading_information.fading_value;
}
