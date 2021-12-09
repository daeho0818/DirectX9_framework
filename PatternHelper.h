#pragma once
class PatternHelper
{
public:
	PatternHelper();
	~PatternHelper();

	void SetPattern(int index, int duration, int coolTime, function<void(float current_count, bool is_end)> func);

	void Update();

private:
	class Pattern
	{
	public:
		int m_index;
		int m_duration;
		int m_coolTime;
		float m_currentTIme;
		function<void(float current_count, bool is_end)> m_func;

		Pattern(int index, int duration, int coolTime, function<void(float current_count, bool is_end)> func)
			: m_index(index), m_duration(duration), m_coolTime(coolTime), m_func(func)
		{
			m_currentTIme = 0;
		}
	};
	list<Pattern*> m_patterns;
	Timer* t_pattern;

	int play_pattern_index;
	bool is_coolTime;
};

