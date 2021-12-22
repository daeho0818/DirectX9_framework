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
	bool IsMousePressed(int button);
	bool IsMouseClick(int button);

	bool IsMouseOver(int button, Button* buttonObj);
	bool IsMouseClick(int button, Button* buttonObj);

	Vector2 GetMousePosition();

private:
	bool now_key[256] = { false, };
	bool old_key[256] = { false, };

	bool left_button_down = false;
	bool left_button_up = false;

	POINT mouse_position;

};
#define INPUT InputManager::Instance()

#define GetKeyDown(key) InputManager::Instance()->KeyDown(key)
#define GetKeyUp(key) InputManager::Instance()->KeyUp(key)
#define GetKey(key) InputManager::Instance()->KeyPress(key)

#define MouseDown(button) InputManager::Instance()->IsMouseDown(button)
#define MouseUp(button) InputManager::Instance()->IsMouseUp(button)
#define MousePressed(button) InputManager::Instance()->IsMousePressed(button)

#define mouse InputManager::Instance()->GetMousePosition()