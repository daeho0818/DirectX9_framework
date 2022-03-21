#include "DXUT.h"
#include "InputManager.h"

InputManager::InputManager()
{
	memset(mouse_button_down, false, 3);
	memset(mouse_button_up, false, 3);
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	for (int i = 0; i < 256; i++) old_key[i] = now_key[i];
	for (int i = 0; i < 256; i++) now_key[i] = GetAsyncKeyState(i);

	for (int i = 0; i < 3; i++)
	{
		mouse_button_up[i] = mouse_button_down[i];
		mouse_button_down[i] = DXUTIsMouseButtonDown(i);
	}

	GetCursorPos(&mouse_position);
	ScreenToClient(DXUTGetHWND(), &mouse_position);
}

bool InputManager::KeyDown(int key)
{
	return now_key[key] && !old_key[key];
}

bool InputManager::KeyUp(int key)
{
	return !now_key[key] && old_key[key];
}

bool InputManager::KeyPress(int key)
{
	return now_key[key] && old_key[key];
}

bool InputManager::IsMouseDown(int button)
{
	if (button >= 3) return false;
	return mouse_button_down[button] && !mouse_button_up[button];
}

bool InputManager::IsMouseUp(int button)
{
	if (button >= 3) return false;
	return mouse_button_up[button] && !mouse_button_down[button];
}

bool InputManager::IsMouse(int button)
{
	if (button >= 3) return false;
	return mouse_button_up[button] && mouse_button_down[button];
}

bool InputManager::IsMouseOver(Button* button)
{
	RECT buttonSize = button->m_size;

	return !mouse_button_down[0] && !mouse_button_up[0] &&
		(mouse_position.x >= buttonSize.left && mouse_position.y >= buttonSize.top &&
			mouse_position.x <= buttonSize.right && mouse_position.y <= buttonSize.bottom);
}

bool InputManager::IsMousePressed(Button* button)
{
	RECT buttonSize = button->m_size;

	bool pressed = IsMouse(0) &&
		(mouse_position.x >= buttonSize.left && mouse_position.y >= buttonSize.top &&
			mouse_position.x <= buttonSize.right && mouse_position.y <= buttonSize.bottom);

	return pressed;
}

bool InputManager::IsMouseClick(Button* button)
{
	RECT buttonSize = button->m_size;

	return IsMouseUp(0) &&
		(mouse_position.x >= buttonSize.left && mouse_position.y >= buttonSize.top &&
			mouse_position.x <= buttonSize.right && mouse_position.y <= buttonSize.bottom);
}

Vector2 InputManager::GetMousePosition()
{
	return Vector2(mouse_position.x, mouse_position.y);
}
