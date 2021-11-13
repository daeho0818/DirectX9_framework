#pragma once
#include "Object.h"
class Player : public Component
{
public:
	Player(Object* object);
	~Player();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void ChkMoveRange();

	RECT move_range;
	const Vector2* m_position;

	float move_speed;
};

