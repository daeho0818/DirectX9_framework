#pragma once
class FireHelper
{
public:
	FireHelper();
	~FireHelper();

	void Update();

	void Fire(Vector2 position, float interval, Vector2 direction, string name, ObjType type, float speed, Image* image);
	void CircleFire(Vector2 position, float interval, string name, ObjType type, float speed, Image* image);

private:
	float current_count;

};

