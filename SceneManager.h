#pragma once
#include "Singleton.h"
#include "Scene.h"
class SceneManager : public Singleton<SceneManager>
{
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
};
#define SCENE SceneManager::Instance()