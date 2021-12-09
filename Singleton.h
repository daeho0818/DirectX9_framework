#pragma once
template <typename T>
class Singleton
{
private:
	static T* p;

public:
	Singleton() {}
	virtual ~Singleton() {}

	static T* Instance()
	{
		if (!p)
			p = new T;
		return p;
	}

	static void Destroy()
	{
		SAFE_DELETE(p);
	}
};
template <typename T>
T* Singleton<T>::p = null;