#pragma once
#include "Component.h"
#include "Image.h"
#include "TimerC.h"
class AnimationC : public Component
{
public:
	AnimationC();
	~AnimationC();

	void SetAnimation(vector<Image*> animation, float frameTime, TimerC* timer);
	Image* GetIndexImg();
private:
	vector<Image*> m_animation;

	int index = 0;
	float m_frameTime;
	TimerC* m_timer;


	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

