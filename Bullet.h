#pragma once
class Bullet : public Component
{
public:
	Bullet(Object* object);
	~Bullet();

	void SetBullet(Vector2 direction, float move_speed, Image* image);
	bool CheckOutRange();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	bool is_set;

	Image* m_image;
	const Vector2* m_position;
	Vector2 m_direction;

	float m_moveSpeed = 0;

};


