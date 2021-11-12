#include "DXUT.h"
#include "AnimationC.h"

AnimationC::AnimationC(Object* object) : Component(object)
{
}

AnimationC::~AnimationC()
{
}

void AnimationC::Init()
{
	m_timer = new Timer();
}

void AnimationC::Update()
{
}

void AnimationC::Render()
{
}

void AnimationC::Release()
{
}

void AnimationC::SetAnimation(string anim_key, float frame_time, bool loop)
{
	m_animation = IMAGE->MakeAnimation(anim_key);
	animation_size = m_animation.size();
	m_index = 0;

	m_timer->SetTimer(frame_time, m_animation.size(), [&]()->void {m_index >= animation_size ? m_index = 0 : m_index++; }, loop);
}

void AnimationC::Play()
{
	m_play = true;

	m_timer->TimerStart();
}

void AnimationC::Stop()
{
	m_timer->TimerStop();
}

Image* AnimationC::GetFrame()
{
	return m_animation[m_index];
}
