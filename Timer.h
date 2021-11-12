#pragma once
class Timer
{
	friend class SceneManager;

public:
	Timer();
	~Timer();

	void SetTimer(float time, int loopCount, function<void()> func, bool loop = false);
	void TimerStart();
	void TimerStop();

private:
	float m_time;
	float startTime;
	int m_loopCount;
	bool m_loop;
	bool is_start;
	bool is_end;
	bool is_stop;
	function<void()> m_func = nullptr;

	virtual void Update();
	virtual void Release();

};

