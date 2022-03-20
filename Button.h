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

	void SetButton( Image* image);
	void SetOnClickListener(function<void()> func);

	RECT m_size;

private:
	RendererC* render = nullptr;

	Image* m_image = nullptr;
	function<void()> onClickListener = nullptr;
};

