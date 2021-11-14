#include "DXUT.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	for (int i = 0; i < 256; i++) old_key[i] = now_key[i];
	for (int i = 0; i < 256; i++) now_key[i] = GetAsyncKeyState(i);

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
	return false;
}

bool InputManager::IsMouseUp(int button)
{
	return false;
}

bool InputManager::IsMouseClick(int button)
{
	return false;
}

Vector2 InputManager::GetMousePosition()
{
	return Vector2(mouse_position.x, mouse_position.y);
}
