#pragma once
#include "Singleton.h"
#include "Scene.h"
#include "Timer.h"
class SceneManager : public Singleton<SceneManager>
{
	friend class Timer;

public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Render();
	void UIRender();
	void Release();

	void AddScene(string key, Scene* scene);
	void ChangeScene(string key);
	Scene* GetCurrentScene();

private:
	map<string, Scene*> m_scenes;

	Scene* current_scene = nullptr;
	Scene* target_scene = nullptr;

	vector<Timer*> m_timers;
};
#define SCENE SceneManager::Instance()