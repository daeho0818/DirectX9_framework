#include "DXUT.h"
#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::Init()
{
	IMAGE->QuickLoad("Effect", "Effect/Effect");
	effect_image = IMAGE->FindImage("Effect");
}

void ParticleManager::Update()
{
	for (var iter = m_particles.begin(); iter != m_particles.end();)
	{
		if ((*iter)->m_destroy)
		{
			SAFE_DELETE((*iter));
			iter = m_particles.erase(iter);
		}
		else
			++iter;
	}

	for (var iter = m_effects.begin(); iter != m_effects.end();)
	{
		(*iter)->m_destroy = (*iter)->m_size <= 0 || (*iter)->m_color.a <= 0;

		if ((*iter)->m_destroy)
		{
			SAFE_DELETE((*iter));
			iter = m_effects.erase(iter);
		}
		else
		{
			if ((*iter)->m_effecting)
				(*iter)->m_effect();
			++iter;
		}
	}
}

void ParticleManager::Render()
{
	for (var iter : m_particles)
	{
		if (iter->m_index >= iter->m_animation.size())
			iter->m_destroy = true;
		else
			RENDER->CenterRender(iter->m_animation[iter->m_index], iter->m_position, iter->m_size);
	}

	for (var iter : m_effects)
	{
		RENDER->CenterRender(effect_image, iter->m_position, iter->m_size, 0, false, iter->m_color);
	}
}

void ParticleManager::Release()
{
	for (var iter : m_particles)
		SAFE_DELETE(iter);
	for (var iter : m_effects)
		SAFE_DELETE(iter);

	m_particles.clear();
	m_effects.clear();
}

void ParticleManager::AddParticleAnim(vector<Image*> animation, Vector2 position, float frameTime, float size)
{
	Particle* particle = new Particle(animation, position, frameTime, size);
	m_particles.push_back(particle);
}

void ParticleManager::AddParticleEffect(Vector2 position, D3DXCOLOR color, ChangeMode changeMode, float size)
{
	Effect* effect = new Effect(position, color, changeMode, size);
	m_effects.push_back(effect);
}

Particle::Particle(vector<Image*> animation, Vector2 position, float frame_time, float size)
{
	m_animation = animation;
	m_position = position;
	m_frameTime = frame_time;
	m_size = size;
	m_index = 0;
	m_destroy = false;

	m_timer = new Timer(frame_time, animation.size(), [&]()->void {m_index++; });
	m_timer->TimerStart();
}

Particle::~Particle()
{
}

Effect::Effect(Vector2 position, D3DXCOLOR color, ChangeMode change_mode, float size)
{
	m_position = position;
	m_color = color;
	m_size = size;
	m_effecting = false;
	m_destroy = false;

	size_value = rand() % 10 / 100.0f;
	alpha_value = 0.05f;

	m_effect = effects[change_mode];
	m_timer = new Timer(0.25f, 0, [&]()->void {m_effecting = true; });
	m_timer->TimerStart();
}

Effect::~Effect()
{
}
