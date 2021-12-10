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

	// images : 기본 상태, 마우스 올렸을 때, 눌려질 때
	void SetButton(Vector2 position, RECT size, Image* images[3]);
	void SetOnClickListener(function<void()> func);

private:
	RECT m_size;
	Image* m_image = nullptr;
	Image* m_image_up = nullptr;
	Image* m_image_press = nullptr;
	function<void()> onClickListener = nullptr;
};

