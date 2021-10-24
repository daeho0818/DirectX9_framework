#include "DXUT.h"
#include "TimerC.h"

TimerC::TimerC()
{
	Init();
}

TimerC::~TimerC()
{
	Release();
}

void TimerC::SetTimer(float time, int loopCount, function<void()> func, bool loop)
{
	TimerClass* timerClass = new TimerClass();
	timerClass->m_time = time;
	timerClass->m_count = loopCount;
	timerClass->m_loop = loop;
	timerClass->m_func = func;
	timerClasses.push_back(timerClass);
}

void TimerC::TimerStart()
{
	for (var iter : timerClasses)
	{
		if (!(iter->isStart) && (iter->m_func != nullptr))
		{
			iter->isStart = true;
		}
	}
}

void TimerC::Init()
{
}

void TimerC::Update()
{
	for (var iter : timerClasses)
	{
		if (!(iter->isStart)) continue;
		iter->startTime += DELTA;

		if (iter->startTime >= iter->m_time)
		{
			iter->m_func();
			if (iter->m_count > 0)
			{
				iter->m_count--;
				iter->startTime = 0;
			}
		}
	}
}

void TimerC::Render()
{
}

void TimerC::Release()
{
}
