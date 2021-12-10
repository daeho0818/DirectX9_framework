#pragma once
#include "Player.h"
#include "Enemy1_1.h"
#include "Enemy1_2.h"
#include "Boss1_1.h"
#include "TestEnemy.h"
class Scene_Stage1 : public Scene
{
public:
	Scene_Stage1();
	~Scene_Stage1();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	void WavePattern1(float current_coolTime, bool is_end);
	void WavePattern2(float current_coolTime, bool is_end);

	PatternHelper* pattern_helper = null;
	Object* m_playerObject = null;
	Player* m_player = null;

	Object* m_bossObject = null;
	Boss1_1* m_boss = null;

	Timer* t_enemy1_spawn = null;
	int enemy1_position_x;

	bool pattern2;
	Vector2 enemy2_position[2];

};
