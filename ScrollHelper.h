#pragma once
#include "Image.h"
class ScrollHelper
{
public:
	ScrollHelper(Image* bg_image);
	~ScrollHelper();

	void Update();
	void Render();

private:
	Image* m_bgImage = nullptr;

	Vector2 bg1_position;
	Vector2 bg2_position;
	Vector2 bg3_position;

	float scroll_speed;
};

