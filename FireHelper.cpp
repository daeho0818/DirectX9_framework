#include "DXUT.h"
#include "FireHelper.h"

FireHelper::FireHelper()
{
	current_count = 0;
}

FireHelper::~FireHelper()
{
}

void FireHelper::Update()
{
	current_count += DELTA;
}

void FireHelper::Fire(Vector2 position, float interval, Vector2 direction, string name, ObjType type, float speed, Image* image)
{
	if (current_count >= interval)
	{
		Bullet* bullet = B_POOL->GetBullet(position, name, type);
		bullet->SetBullet(direction, speed, image);
		current_count = 0;
	}
}

void FireHelper::CircleFire(Vector2 position, float interval, string name, ObjType type, float speed, Image* image)
{
	Bullet* bullet;

	for (int i = 0; i < 360; i += 1 * interval)
	{
		bullet = B_POOL->GetBullet(position, name, type);
		bullet->SetBullet(Vector2(cos(D3DXToRadian(i)), sin(D3DXToRadian(i))), speed, image);
	}
}
