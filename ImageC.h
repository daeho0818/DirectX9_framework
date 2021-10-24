#pragma once
#include "LoadingManager.h"
#include "RenderManager.h"
#include "Component.h"
#include "Image.h"
class ImageC : public Component
{
	friend class LoadingManager;
public: 
	ImageC();
	~ImageC();

	Image* GetImage(string key);
	vector<Image*> GetAnimation(string key);

private:
	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

