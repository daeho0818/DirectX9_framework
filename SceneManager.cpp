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
		m_scrollHelper->Update();

	if (current_scene) current_scene->Update();

	// 화면 Fading이 끝났다면
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

	for (var iter : m_timers)
		SAFE_DELETE(iter);
	for (var iter : m_scenes)
		SAFE_DELETE(iter.second);

	SAFE_DELETE(m_scrollHelper);

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
		return;

	CAMERA->FadingScreen(10, false, true);

	var find = m_scenes.find(key);
	target_scene = find->second;
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
	{
		current_scene->Release();
		OBJECT->DestroyAllObject();
	}

	target_scene->Init();
	current_scene = target_scene;
	target_scene = null;
	CAMERA->FadingScreen(5, true, true);
}
