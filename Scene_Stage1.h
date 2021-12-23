#pragma once
#include "Player.h"
#include "Enemy1_1.h"
#include "Enemy1_2.h"
#include "Enemy1_3.h"
#include "Enemy1_4.h"
#include "Boss1_1.h"
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
	void WavePattern3(float current_coolTime, bool is_end);
	void WavePattern4(float current_coolTime, bool is_end);
	void WavePattern5(float current_coolTime, bool is_end);

	// helpers
	PatternHelper* pattern_helper = nullptr;
	ScrollHelper* scroll_helper = nullptr;

	// objects
	Object* m_playerObject = nullptr;
	Player* m_player = nullptr;

	Object* m_bossObject = nullptr;
	Boss1_1* m_boss = null;

	// releted field of stage patterns
	Timer* t_enemy1_spawn = nullptr;
	int enemy1_position_x;

	bool pattern2;
	Vector2 enemy2_position[2];

	Timer* t_enemy3_spawn = nullptr;
	Vector2 enemy3_spawn_positions[3];
	int enemy3_spawn_count = 0;

	bool pattern5;

	// related boss help
	char boss_appear_str[256] = "";
	int boss_appear_count;
	Timer* boss_appear_timer = nullptr;

};
