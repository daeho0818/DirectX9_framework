#pragma once
class Timer
{
	friend class SceneManager;

public:
	Timer(float time, int loopCount, function<void()> func, bool loop = false);
	~Timer();

	void TimerStart();
	void TimerStop();
	float GetTime();

private:
	float m_time;
	float startTime;
	int m_loopCount;
	bool m_loop;
	bool is_start;
	bool is_end;
	bool is_stop;
	function<void()> m_func = null;

	void Update();

};

