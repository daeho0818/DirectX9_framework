#pragma once
#include "Object.h"
class Player : public Component
{
public:
	Player(Object* object);
	~Player();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

