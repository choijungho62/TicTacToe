#pragma once
#include "Scene.h"

class VertexArrayGo;

class SceneGame : public Scene
{
protected:

	VertexArrayGo* background;
	sf::FloatRect wallBounds;

public:
	SceneGame();
	virtual ~SceneGame() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	VertexArrayGo* CreateBackGround(sf::Vector2i size, sf::Vector2f tileSize, sf::Vector2f texSize, std::string textureId);

	virtual void HandleClickEvent(sf::Vector2f clickPosition);

	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;

	VertexArrayGo* GetBackground();
};

