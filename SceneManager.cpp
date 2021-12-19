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
	srand(time(null));
}

void SceneManager::Update()
{
	if (m_scrollHelper)
		m_scrollHelper->Render();

	if (current_scene) current_scene->Update();

	if (target_scene && !CAMERA->IsAction(3))
	{
		SceneLoading();
	}

	for (var iter = m_timers.begin(); iter != m_timers.end();)
	{
		if ((*iter)->is_end)
		{
			SAFE_DELETE(*iter);
			iter = m_timers.erase(iter);
		}
		else
		{
			(*iter)->Update();
			++iter;
		}
	}
}

void SceneManager::Render()
{
	if (m_scrollHelper)
		m_scrollHelper->Render();

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
	for (var iter : m_timers)
		SAFE_DELETE(iter);

	m_timers.clear();
	m_scenes.clear();
}

void SceneManager::AddScene(string key, Scene* scene)
{
	if (m_scenes.find(key) == m_scenes.end())
	{
		m_scenes.insert(make_pair(key, scene));
		scene->scene_name = key;
	}
}

void SceneManager::ChangeScene(string key)
{
	// 이미 씬을 바꾸는 중인지 검사
	if (target_scene)
		for (var iter : m_scenes)
			if (iter.second == target_scene) return;

	if (CAMERA->IsAction(3) && target_scene)
	{
		CAMERA->StopAction(3);
		SceneLoading();
	}
	CAMERA->FadingScreen(10, false, true);

	var find = m_scenes.find(key);
	target_scene = find->second;

	OBJECT->DestroyAllObject();
}

Scene* SceneManager::GetActiveScene()
{
	return current_scene;
}

void SceneManager::SetScrollHelper(ScrollHelper* scroll_helper)
{
	m_scrollHelper = scroll_helper;
}

void SceneManager::SceneLoading()
{
	if (current_scene)
		current_scene->Release();

	target_scene->Init();
	current_scene = target_scene;
	target_scene = null;
	CAMERA->FadingScreen(5, true, true);
}
