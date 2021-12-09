#pragma once
#include "Singleton.h"

enum ChangeMode
{
	Small = 1,
	Big = 2,
	FadeOut = 4,

	Small_FadeOut = 5,
	Big_FadeOut = 6
};

class Particle
{
public:
	Particle(vector<Image*> animation, Vector2 position, float frame_time, float size);
	~Particle();

	vector<Image*> m_animation;
	Vector2 m_position;
	float m_size;
	bool m_destroy;
	int m_index;

private:
	Timer* m_timer;
	float m_frameTime;
};

class Effect
{
public:
	Effect(Vector2 position, D3DXCOLOR color, ChangeMode change_mode, float size);
	~Effect();

	Vector2 m_position;
	D3DXCOLOR m_color;
	function<void()> m_effect;
	float m_size;
	bool m_effecting;
	bool m_destroy;

	function<void()> effects[7] =
	{
		null,

		[&]()->void {
			if (m_size > 0) m_size -= size_value;
			else m_size = 0; },

		[&]()->void { if (m_size < 50) m_size += size_value; },

		null,

		[&]()->void {
			if (m_color.a > 0) m_color.a -= alpha_value;
			else m_color.a = 0; },

		[&]()->void {
			if (m_size > 0) m_size -= size_value;
			else m_size = 0;
			if (m_color.a > 0) m_color.a -= alpha_value;
			else m_color.a = 0; },

		[&]()->void {
			if (m_size < 50) m_size += size_value;
			if (m_color.a > 0) m_color.a -= alpha_value;
			else m_color.a = 0; }
	};

private:
	Timer* m_timer;
	float size_value;
	float alpha_value;
};

class ParticleManager : public Singleton<ParticleManager>
{
public:
	ParticleManager();
	~ParticleManager();

	void Init();
	void Update();
	void Render();
	void Release();

	void AddParticleAnim(vector<Image*> animation, Vector2 position, float frameTime, float size = 1);
	// changeMode = ChangeMode::Big | ChangeMode::FadeOut 이런식으로 적용
	void AddParticleEffect(Vector2 position, D3DXCOLOR color, ChangeMode changeMode, float size = 1);

private:
	vector<Particle*> m_particles;
	vector<Effect*> m_effects;

	Image* effect_image;
};
#define PARTICLE ParticleManager::Instance()
