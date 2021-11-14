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

#define GetKeyDown(key) this->KeyDown(key)
#define GetKeyUp(key) this->KeyUp(key)
#define GetKey(key) this->KeyPress(key)

#define MouseDown(button) this->MouseDown(button)
#define MouseUp(button) this->MouseUp(button)
#define MouseClick(button) this->MouseClick(button)

#define mouse mouse_position