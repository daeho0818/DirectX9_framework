#pragma once
#include <SDKsound.h>
class Sound
{
public:
	Sound(LONG volume, bool loop, CSound* cSound);
	~Sound();

	LONG m_volume;
	bool m_loop;
	CSound* m_cSound = nullptr;
};

