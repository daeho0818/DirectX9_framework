#pragma once
#include "Singleton.h"
class ParticleManager : public Singleton<ParticleManager>
{
public:
	ParticleManager();
	~ParticleManager();
};
#define PARTICLE ParticleManager::Instance()