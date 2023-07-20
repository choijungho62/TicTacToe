#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneGame.h"

void SceneMgr::ChangeScene(SceneId id)
{
	currentScene->Exit(); //현재 열려있는 씬 종료
	currentSceneId = id;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter(); //새로 열 씬 시작
}

Scene* SceneMgr::GetCurrScene() const
{
	return currentScene;
}

void SceneMgr::Init()
{
	if (!scenes.empty())
	{
		Release();
	}

	scenes.push_back(new SceneGame);

	for (auto scene : scenes)
	{
		scene->Init();
	}
	currentSceneId = startSceneId;
	currentScene = scenes[int(currentSceneId)];
	currentScene->Enter();
}

void SceneMgr::Release()
{
	if (scenes.empty())
	{
		return;
	}

	for (auto scene : scenes)
	{
		//scene->Release();
		delete scene;
	}
	scenes.clear();

	currentSceneId = SceneId::None;
	currentScene = nullptr;
}

void SceneMgr::Update(float dt)
{
	currentScene->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	currentScene->Draw(window);
}