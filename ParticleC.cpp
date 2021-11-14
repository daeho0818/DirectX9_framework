#include "DXUT.h"
#include "ParticleC.h"

ParticleC::ParticleC(Object* object) : Component(object)
{
}

ParticleC::~ParticleC()
{
}

void ParticleC::AddParticleAnim(vector<Image*> animation, Vector2 position, float frameTime, float size)
{
	m_animation = animation;
	m_position = position;
	m_frameTime = frameTime;
	m_size = size;

	isParticleAnimation = true;
}

void ParticleC::AddParticleEffect(Image* image, Vector2 position, D3DXCOLOR color, ChangeMode changeMode, float size, float destroyTime)
{
	m_image = image;
	m_position = position;
	m_color = color;
	m_changeMode = changeMode;
	m_size = size;
	m_destroyTime = destroyTime;

	isParticleEffect = true;
}

void ParticleC::Init()
{
}

void ParticleC::Update()
{
	if (isParticleAnimation)
	{

	}
	else if (isParticleEffect)
	{
 	}
	switch (m_changeMode)
	{
	case Small:
		break;
	case Big:
		break;
	case FadeIn:
		break;
	case FadeOut:
		break;
	case Small_FadeIn:
		break;
	case Small_FadeOut:
		break;
	case Big_FadeIn:
		break;
	case Big_FadeOut:
		break;
	default:
		break;
	}
}

void ParticleC::Render()
{
}

void ParticleC::UIRender()
{
}

void ParticleC::Release()
{
	m_animation.clear();
}
