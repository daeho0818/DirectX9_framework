#include "DXUT.h"
#include "PatternHelper.h"

PatternHelper::PatternHelper()
{
	play_pattern_index = 0;
	is_coolTime = false;
}

PatternHelper::~PatternHelper()
{
	for (var iter : m_patterns)
		SAFE_DELETE(iter);
	m_patterns.clear();
}

void PatternHelper::SetPattern(int index, int duration, int coolTime, function<void(float current_count, bool is_end)> func)
{
	if (!m_patterns.empty())
		for (var iter = m_patterns.begin(); iter != m_patterns.end();)
		{
			if ((*iter)->m_index == index)
			{
				SAFE_DELETE(*iter);
				iter = m_patterns.erase(iter);
				break;
			}
			else ++iter;
		}

	m_patterns.push_back(new Pattern(index, duration, coolTime, func));
}

void PatternHelper::Update()
{
	for (var iter : m_patterns)
	{
		if (is_coolTime || iter->m_index != play_pattern_index) continue;

		iter->m_currentTIme += DELTA;
		iter->m_func(iter->m_currentTIme, !(iter->m_currentTIme <= (float)iter->m_duration));

		if (!(iter->m_currentTIme <= (float)iter->m_duration))
		{
			iter->m_currentTIme = 0;
			is_coolTime = true;
			t_pattern = new Timer(iter->m_coolTime, 0, [&]()->void {is_coolTime = false; });
			t_pattern->TimerStart();
			play_pattern_index = rand() % m_patterns.size();
		}
	}
}
