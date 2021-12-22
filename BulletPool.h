#pragma once
class Bullet;
class BulletPool : public Singleton<BulletPool>
{
public:
	BulletPool();
	~BulletPool();

	Bullet* GetBullet(Vector2 position, string bullet_name, ObjType bullet_type);
	void ReturnBullet(Bullet* bullet);

private:
	vector<Bullet*> m_bullets;

};
#define B_POOL BulletPool::Instance()