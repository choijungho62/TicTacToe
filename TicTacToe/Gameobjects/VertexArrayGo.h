#pragma once
#include "GameObject.h"

class VertexArrayGo : public GameObject
{
protected:
	std::string textureId;
	sf::Texture* texture;
	sf::Vector2f originPos;

public:
	sf::VertexArray vertexArray;

	VertexArrayGo(const std::string& textureId = "", const std::string& name = "");
	virtual ~VertexArrayGo() override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Release() override;

	virtual void SetPosition(const sf::Vector2f& position);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin) override;
	virtual void SetOrigin(float x, float y) override;
};