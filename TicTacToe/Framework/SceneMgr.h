#pragma once
#include "Singleton.h"
#include "Scene.h"


class SceneMgr : public Singleton<SceneMgr>
{
	friend Singleton<SceneMgr>;

protected:
	SceneMgr() = default;
	virtual ~SceneMgr() override = default;

	std::vector<Scene*> scenes;
	SceneId currentSceneId = SceneId::None;
	Scene* currentScene = nullptr;

	SceneId startSceneId = SceneId::Game;

public:

	void ChangeScene(SceneId id); //���� �����ϴ� �Լ�
	Scene* GetCurrScene() const;

	void Init();
	void Release();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

#define SCENE_MGR (SceneMgr::Instance())

