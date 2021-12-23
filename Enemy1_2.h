#pragma once
class Enemy1_2 : public Component
{
public:
	Enemy1_2(Object* object);
	~Enemy1_2();

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;
	
	void SetEnemy(int index);

private:
	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	Timer* wait_timer = nullptr;

	Image* bullet_image = nullptr;

	int m_index;
	int oper_values[4];

	float sin_value;

	bool move_able;

};