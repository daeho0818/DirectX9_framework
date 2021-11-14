#pragma once
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
	bool IsMouseClick(int button);

	Vector2 GetMousePosition();

private:
	bool now_key[256] = { false, };
	bool old_key[256] = { false, };

	POINT mouse_position;

};
#define INPUT InputManager::Instance()

#define GetKeyDown(key) INPUT->KeyDown(key)
#define GetKeyUp(key) INPUT->KeyUp(key)
#define GetKey(key) INPUT->KeyPress(key)

#define MouseDown(button) INPUT->MouseDown(button)
#define MouseUp(button) INPUT->MouseUp(button)
#define MouseClick(button) INPUT->MouseClick(button)

#define mouse mouse_position