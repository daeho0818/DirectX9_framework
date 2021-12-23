#pragma once
#include "Player.h"
class Enemy1_4 : public Component
{
public:
	Enemy1_4(Object* object);
	~Enemy1_4();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void SetEnemy(Player* player, int enemy_index);

private:
	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	Image* bullet_image = nullptr;

	Player* m_player = nullptr;

	Vector2 move_direction;

	int reflect_count;

};

