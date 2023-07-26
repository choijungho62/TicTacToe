#pragma once
#include "Scene.h"

class VertexArrayGo;

class SceneGame : public Scene
{
protected:

	VertexArrayGo* background;
	sf::FloatRect wallBounds;
	bool playerOneTurn = true; // 1P = X, 2P = O
	std::vector<std::vector<bool>> tileStates; // 타일의 클릭 상태를 저장하는 2차원 배열

public:
	SceneGame();
	virtual ~SceneGame() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;

	VertexArrayGo* CreateBackGround(sf::Vector2i size, sf::Vector2f tileSize, sf::Vector2f texSize, std::string textureId);

	virtual void HandleClickEvent(sf::Vector2f clickPosition);

	VertexArrayGo* GetBackground();
};

