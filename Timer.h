#pragma once
class Timer
{
	friend class SceneManager;

public:
	Timer();
	~Timer();

	void SetTimer(float time, int loopCount, function<void()> func, bool loop = false);
	void TimerStart();

private:
	float m_time = 0;
	float startTime = 0;
	int m_loopCount = 0;
	bool m_loop = false;
	bool is_start = false;
	bool is_end = false;
	function<void()> m_func = nullptr;

	virtual void Update();
	virtual void Release();

};

