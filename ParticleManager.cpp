#include "DXUT.h"
#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::Update()
{
	for(var iter : )
}

void ParticleManager::Render()
{
}

void ParticleManager::Release()
{
}

void ParticleManager::AddParticleAnim(vector<Image*> animation, Vector2 position, float frameTime, float size)
{
	Particle* particle = new Particle(animation, position, frameTime, size);
	m_particles.push_back(particle);
}

void ParticleManager::AddParticleEffect(Image* image, Vector2 position, D3DXCOLOR color, ChangeMode changeMode, float size, float destroyTime)
{
	Effect* effect = new Effect(image, position, color, changeMode, size, destroyTime);
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
}

Particle::~Particle()
{
}

Effect::Effect(Image* image, Vector2 position, D3DXCOLOR color, ChangeMode change_mode, float size, float destroy_time)
{
	m_image = image;
	m_color = color;
	m_changeMode = change_mode;
	m_destroyTime;
}

Effect::~Effect()
{
}
