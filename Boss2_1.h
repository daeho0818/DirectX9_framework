#pragma once
#include "Player.h"
#include "PatternHelper.h"
#include "Cannon.h"
class Boss2_1 : public Component
{
	friend class Cannon;
public:
	Boss2_1(Object* object);
	~Boss2_1();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;


private:
	void Pattern1(float current_count, bool is_end);

	void SetAllPatterns();
	void SpawnAnimation();
		
	Player* m_player = nullptr;

	PatternHelper* pattern_helper = nullptr;

	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	Image* bullet_image = nullptr;

	vector<Cannon*> cannons;

	int anim_complete_count = 0;

	bool is_spawned;

};

