#pragma once
class Enemy1_3 : public Component
{
public:
	Enemy1_3(Object* object);
	~Enemy1_3();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	void CircleBullet(float speed, float interval);

	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	Image* bullet_image = nullptr;

	Timer* wait_timer = nullptr;

	BulletPool<Bullet>* bullet_pool = nullptr;

	bool move_able;
};

