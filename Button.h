#pragma once
class Button : public Component
{
public:
	Button(Object* object);
	~Button();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void SetButton(Vector2 position, RECT size);
	void SetOnClickListener(function<void()> func);

private:
	RECT m_size;
	function<void()> onClickListener;
};

