#pragma once
class Enemy1_4 : public Component
{
public:
	Enemy1_4(Object* object);
	~Enemy1_4();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;
};

