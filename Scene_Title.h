#pragma once
class Scene_Title : public Scene
{
public:
	Scene_Title();
	~Scene_Title();

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

};

