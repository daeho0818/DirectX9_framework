#pragma once
#include "Singleton.h"
#include "Scene.h"
#include "Timer.h"
#include "ScrollHelper.h"
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

	void SetScrollHelper(ScrollHelper* scroll_helper);

private:
	map<string, Scene*> m_scenes;

	Scene* current_scene = nullptr;
	Scene* target_scene = nullptr;

	vector<Timer*> m_timers;

	ScrollHelper* m_scrollHelper = nullptr;

	void SceneLoading();
};
#define SCENE SceneManager::Instance()