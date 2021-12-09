#pragma once
class Enemy1_1 : public Component
{
public:
	Enemy1_1(Object* object);
	~Enemy1_1();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	void Fire();

	BoxColliderC* collider = null;
	RendererC* renderer = null;

	Image* bullet_image = null;

	float check_time;
	float fire_check_time;
	bool is_fire;
};

