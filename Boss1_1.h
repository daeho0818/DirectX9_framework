#pragma once
#include "Player.h"
#include "BulletPool.h"
#include "PatternHelper.h"

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

	Player* m_player = nullptr;

private:
	void Pattern1(float current_count, bool is_end);
	void Pattern2(float current_count, bool is_end);
	void Pattern3(float current_count, bool is_end);

	void SpawnAnimation();

	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	Image* bullet_image = nullptr;

	PatternHelper* pattern_helper = nullptr;

	Timer* t_pattern_3 = nullptr;
	Timer* t_pattern_3_1 = nullptr;

	bool is_spawned;

};

