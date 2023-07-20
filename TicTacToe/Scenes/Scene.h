#pragma once

class GameObject;

class Scene
{
protected:

	Scene(const Scene&) = delete;
	Scene& operator = (const Scene&) = delete;

	SceneId sceneId;

	std::vector < std::tuple<ResourceTypes, std::string>>resources;
	std::list<GameObject*> gameObjects;

	sf::View worldView;
	sf::View uiView;

public:
	Scene(SceneId id = SceneId::None);
	virtual ~Scene();

	GameObject* FindGo(const std::string& name);
	void FindGos(std::list<GameObject*>& list, const std::string& name);

	bool Exist(GameObject* go);
	GameObject* AddGo(GameObject* go);
	void RemoveGo(GameObject* go);
	void SortGos();

	virtual void Init() = 0;
	virtual void Release() {}

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);
};

