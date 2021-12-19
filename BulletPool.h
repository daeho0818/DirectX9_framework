#pragma once
class Bullet;
class BulletPool
{
public:
	BulletPool();
	~BulletPool();

	Bullet* GetBullet(Vector2 position, string bullet_name, ObjType bullet_type);
	void ReturnBullet(Bullet* bullet);

private:
	vector<Bullet*> m_bullets;

};