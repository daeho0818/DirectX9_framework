#pragma once
class PatternHelper
{
public:
	PatternHelper();
	~PatternHelper();

	void SetPattern(int duration, int coolTime, function<void()> func);

	void Update();

private:
	class Pattern
	{
	public:
		int m_duration;
		int m_coolTime;
		function<void()> m_func;
	};
	list<Pattern> m_functions;
};

