#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceMgr.h"

Scene::Scene(SceneId id) : sceneId(id)
{
}

Scene::~Scene()
{
	Release();
}

GameObject* Scene::FindGo(const std::string& name)
{
	auto compare = [name](GameObject* go) {return go->GetName() == name; };
	auto it = std::find_if(gameObjects.begin(), gameObjects.end(), compare);
	if (it == gameObjects.end())
		return nullptr;
	return *it;
	/*
	for (auto go : gameObjects)
	{
		if (go->GetName() == name)
		{
			return go;
		}
	}

	return nullptr;
	*/
}

void Scene::FindGos(std::list<GameObject*>& list, const std::string& name)
{
	//list.clear();
	for (auto go : gameObjects)
	{
		if (go->GetName() == name)
		{
			list.push_back(go);
		}
	}
}

bool Scene::Exist(GameObject* go)
{
	return std::find(gameObjects.begin(), gameObjects.end(), go) != gameObjects.end();
}

GameObject* Scene::AddGo(GameObject* go)
{
	if (!Exist(go))
	{
		gameObjects.push_back(go);
	}

	return go;
}

void Scene::RemoveGo(GameObject* go)
{
	gameObjects.remove(go);
	//delete go;
}

void Scene::SortGos()
{
	gameObjects.sort([](GameObject* lhs, GameObject* rhs) {
		if (lhs->sortLayer != rhs->sortLayer)
			return lhs->sortLayer < rhs->sortLayer;
		return lhs->sortOrder < rhs->sortOrder;
		});
}

sf::Vector2f Scene::ScreenToWorldPos(sf::Vector2f screenPos)
{
	return window.mapPixelToCoords((sf::Vector2i)screenPos, worldView);
}

sf::Vector2f Scene::ScreenToUiPos(sf::Vector2f screenPos)
{
	return window.mapPixelToCoords((sf::Vector2i)screenPos, uiView);
}

sf::Vector2f Scene::WorldPosToScreen(sf::Vector2f worldPos)
{
	return (sf::Vector2f)window.mapCoordsToPixel(worldPos, worldView);
}

sf::Vector2f Scene::UiPosPosToScreen(sf::Vector2f uiPos)
{
	return (sf::Vector2f)window.mapCoordsToPixel(uiPos, uiView);
}

void Scene::Enter()
{
	RESOURCE_MGR.Load(resources);
	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void Scene::Exit()
{
	RESOURCE_MGR.UnLoad(resources);
}

void Scene::Update(float dt)
{
	for (auto go : gameObjects)
	{
		if (go->GetActive())
		{
			go->Update(dt);
		}
	}
}

void Scene::Draw(sf::RenderWindow& window)
{

	for (auto go : gameObjects)
	{
		if (go->GetActive())
		{
			go->Draw(window);
		}
	}
}
