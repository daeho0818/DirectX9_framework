#pragma once
class Cannon : public Component
{
public:
	Cannon(Object* object);
	~Cannon();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void SetCannon(Image* image);
	void Rotation(Vector2 target_position);

private:
	RendererC* renderer = nullptr;
	BoxColliderC* collider = nullptr;

};

