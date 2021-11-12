#include "DXUT.h"
#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::SetTimer(float time, int loopCount, function<void()> func, bool loop)
{
	m_time = time;
	m_loopCount = loopCount;
	m_func = func;

	is_start = false;

	SCENE->m_timers.push_back(this);
}

void Timer::TimerStart()
{
	if (!is_start) is_start = true;
	else is_stop = false;
}

void Timer::TimerStop()
{
	is_stop = true;
}

void Timer::Update()
{
	if (!is_start || is_stop) return;

	startTime += DELTA;

	if (startTime >= m_time)
	{
		m_func();
		if (m_loopCount > 1 || m_loop)
		{
			m_loopCount--;
			startTime = 0;
		}
		else is_end = true;
	}

}

void Timer::Release()
{
	delete this;
}
