#pragma once
class TestEnemy : public Component
{
public :
	TestEnemy(Object* object);
	~TestEnemy();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	RendererC* renderer;
	BoxColliderC* collider;

};

