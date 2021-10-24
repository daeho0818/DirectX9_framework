#include "DXUT.h"
#include "Sound.h"

Sound::Sound(LONG volume, bool loop, CSound* cSound)
	:m_volume(volume), m_loop(loop), m_cSound(cSound)
{
}

Sound::~Sound()
{
}
