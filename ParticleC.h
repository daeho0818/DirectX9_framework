#pragma once
#include "Image.h"
#include "Component.h"

enum ChangeMode
{
	Small = 1,
	Big = 2,
	FadeIn = 4,
	FadeOut = 8,

	Small_FadeIn = 5,
	Small_FadeOut = 9,

	Big_FadeIn = 6,
	Big_FadeOut = 10
};

class ParticleC : public Component
{
public:
	ParticleC(Object* object);
	~ParticleC();

	void AddParticleAnim(vector<Image*> animation, Vector2 position, float frameTime, float size = 1);
	// 사용 방법 : changeMode = (ChangeMode::Small) | (ChangeMode:: FadeIn)
	void AddParticleEffect(Image* image, Vector2 position, D3DXCOLOR color, ChangeMode changeMode, float size = 1, float destroyTime = 1);

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	ChangeMode m_changeMode;
	Image* m_image;
	vector<Image*> m_animation;
	Vector2 m_position;
	D3DXCOLOR m_color;
	float m_frameTime;
	float m_size;
	float m_destroyTime;

	bool isParticleAnimation;
	bool isParticleEffect;

};
