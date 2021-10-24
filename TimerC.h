#pragma once
#include "Component.h"
class TimerC : public Component
{
public:
	TimerC();
	~TimerC();

	void SetTimer(float time, int loopCount, function<void()> func, bool loop = false);
	void TimerStart();

private:
	class TimerClass
	{
	public:
		float m_time = 0;
		float startTime = 0;
		int m_count = 0;
		bool m_loop = false;
		bool isStart = false;
		function<void()> m_func = nullptr;
	};
	list<TimerClass*> timerClasses;

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

