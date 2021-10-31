#include "DXUT.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	if (current_scene) current_scene->Update();

	if (target_scene)
	{
		if (current_scene)
			current_scene->Release();
		target_scene->Init();
		current_scene = target_scene;
		target_scene = nullptr;
	}
}

void SceneManager::Render()
{
	if (current_scene) current_scene->Render();
}

void SceneManager::UIRender()
{
	if (current_scene) current_scene->UIRender();
}

void SceneManager::Release()
{
	if (current_scene) current_scene->Release();

	for (var iter : m_scenes)
		SAFE_DELETE(iter.second);

	m_scenes.clear();
}

void SceneManager::AddScene(string key, Scene* scene)
{
	if (m_scenes.find(key) == m_scenes.end())
		m_scenes.insert(make_pair(key, scene));
}

void SceneManager::ChangeScene(string key)
{
	var find = m_scenes.find(key);
	if (find != m_scenes.end()) target_scene = find->second;
}

Scene* SceneManager::GetCurrentScene()
{
	return current_scene;
}
