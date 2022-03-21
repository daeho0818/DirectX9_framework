#pragma once
#include "Button.h"
class InputManager : public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();

	void Update();

	bool KeyDown(int key);
	bool  KeyUp(int key);
	bool KeyPress(int key);

	bool IsMouseDown(int button);
	bool IsMouseUp(int button);
	bool IsMouse(int button);

	// Button 상호작용
	bool IsMouseOver(Button* button);
	bool IsMousePressed(Button* button);
	bool IsMouseClick(Button* button);

	Vector2 GetMousePosition();

private:
	bool now_key[256] = { false, };
	bool old_key[256] = { false, };

	bool mouse_button_down[3];
	bool mouse_button_up[3];

	POINT mouse_position;

};
#define INPUT InputManager::Instance()

#define GetKeyDown(key) InputManager::Instance()->KeyDown(key)
#define GetKeyUp(key) InputManager::Instance()->KeyUp(key)
#define GetKey(key) InputManager::Instance()->KeyPress(key)

#define MouseDown(button) InputManager::Instance()->IsMouseDown(button)
#define MouseUp(button) InputManager::Instance()->IsMouseUp(button)
#define Mouse(button) InputManager::Instance()->IsMouse(button)

#define mouse InputManager::Instance()->GetMousePosition()