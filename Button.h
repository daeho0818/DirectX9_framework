#pragma once
class Button : public Component
{
public:
	Button(Object* object);
	~Button();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	// images : �⺻ ����, ���콺 �÷��� ��, ������ ��
	void SetButton(Vector2 position, RECT size, Image* images[3]);
	void SetOnClickListener(function<void()> func);

private:
	RECT m_size;
	Image* m_image = nullptr;
	Image* m_image_up = nullptr;
	Image* m_image_press = nullptr;
	function<void()> onClickListener = nullptr;
};

