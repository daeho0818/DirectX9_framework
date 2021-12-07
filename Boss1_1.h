#pragma once
class Boss1_1 : public Component
{
public:
	Boss1_1(Object* object);
	~Boss1_1();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	void Pattern1();
	void Pattern2();

	BoxColliderC* collider;
	RendererC* renderer;

	Image* bullet_image;

	Timer* timer = nullptr;

};

