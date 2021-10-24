#include "DXUT.h"
#include "AnimationC.h"

AnimationC::AnimationC()
{
}

AnimationC::~AnimationC()
{
}

void AnimationC::SetAnimation(vector<Image*> animation, float frameTime, TimerC* timer)
{
	m_animation = animation;
	m_frameTime = frameTime;
	m_timer = timer;
}

Image* AnimationC::GetIndexImg()
{
	return m_animation[index];
}

void AnimationC::Init()
{
	(*m_timer).SetTimer(1, 0, [&]()->void {index++; }, true);
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
