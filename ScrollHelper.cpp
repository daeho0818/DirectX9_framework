#include "DXUT.h"
#include "ScrollHelper.h"

ScrollHelper::ScrollHelper(Image* bg_image)
	:m_bgImage(bg_image)
{
	bg1_position = CENTER - Vector2(0, m_bgImage->info.Height);
	bg2_position = CENTER;
	bg3_position = CENTER + Vector2(0, m_bgImage->info.Height);

	SCENE->SetScrollHelper(this);
}

ScrollHelper::~ScrollHelper()
{
}

void ScrollHelper::Update()
{
	bg1_position.y += DELTA * 5;
	bg2_position.y += DELTA * 5;
	bg3_position.y += DELTA * 5;

	if (bg3_position.y > m_bgImage->info.Height * 2)
		bg3_position.y = bg1_position.y - m_bgImage->info.Height;

	else if (bg2_position.y > m_bgImage->info.Height * 2)
		bg2_position.y = bg3_position.y - m_bgImage->info.Height;

	else if (bg1_position.y > m_bgImage->info.Height * 2)
		bg1_position.y = bg2_position.y - m_bgImage->info.Height;
}

void ScrollHelper::Render()
{
	RENDER->CenterRender(m_bgImage, bg1_position);
	RENDER->CenterRender(m_bgImage, bg2_position);
	RENDER->CenterRender(m_bgImage, bg3_position);
}
