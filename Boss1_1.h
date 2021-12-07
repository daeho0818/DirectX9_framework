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

	void CircleBullet(float speed, float interval = 1);

	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	Image* bullet_image = nullptr;

	Timer* t_pattern1 = nullptr;
	bool b_pattern1;

};

