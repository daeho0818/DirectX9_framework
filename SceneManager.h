#pragma once
#include "Singleton.h"
#include "Scene.h"
#include "Timer.h"
class SceneManager : public Singleton<SceneManager>
{
	friend class Timer;
	friend class Scene;

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
	Scene* GetActiveScene();

private:
	map<string, Scene*> m_scenes;

	Scene* current_scene = null;
	Scene* target_scene = null;

	vector<Timer*> m_timers;

	void SceneLoading();
};
#define SCENE SceneManager::Instance()