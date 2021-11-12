#pragma once
class AnimationC : public Component
{
public:
	AnimationC(Object* object);
	~AnimationC();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void SetAnimation(string anim_key, float frame_time, bool loop = true);
	void Play();
	void Stop();

	Image* GetFrame();
	
private:
	vector<Image*> m_animation;
	Timer* m_timer;

	int m_index;
	int animation_size;

	bool m_play;
};

