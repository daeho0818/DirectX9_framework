#pragma once
#include "Boss2_1.h"
class Cannon : public Component
{
	friend class Boss2_1;
public:
	Cannon(Object* object);
	~Cannon();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void SetCannon(Boss2_1* boss, Image* image, int index, int rotation);
	void Rotation(Vector2 target_position);
	void Reset();

private:
	RendererC* renderer = nullptr;
	BoxColliderC* collider = nullptr;

	Boss2_1* m_boss = nullptr;

	int cannon_index = 0;
	int m_rotation;

};

