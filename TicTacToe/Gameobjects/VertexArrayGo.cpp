#include "stdafx.h"
#include "VertexArrayGo.h"
#include "ResourceMgr.h"

VertexArrayGo::VertexArrayGo(const std::string& textureId, const std::string& name)
	:GameObject(name), textureId(textureId), texture(nullptr)
{

}
VertexArrayGo::~VertexArrayGo()
{

}

void VertexArrayGo::Init()
{

}
void VertexArrayGo::Reset()
{
	texture = RESOURCE_MGR.GetTexture(textureId);
}
void VertexArrayGo::Update(float dt)
{
	texture = RESOURCE_MGR.GetTexture(textureId);
}

void VertexArrayGo::Draw(sf::RenderWindow& window)
{
	window.draw(vertexArray, texture);
}

void VertexArrayGo::Release()
{

}

void VertexArrayGo::SetPosition(const sf::Vector2f& p)
{
	/*편재 포지션에서 변경할 포지션 사이의 차를 구하면 변화량을 알 수 잇음.
	이 변화량을 각 정점에 적용해주면 포지션이 변경됨.*/
	sf::Vector2f delta = p - position; //변화량
	position = p;

	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += delta;
	}

}

void VertexArrayGo::SetPosition(float x, float y)
{
	SetPosition({ x, y });
}

void VertexArrayGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);

	if (origin == Origins::CUSTOM)
		return;

	/*prevOrigin: 기존의 오리진, originPosition: 변경할 오리진*/
	sf::Vector2f prevOrigin = originPos;
	sf::FloatRect bounds = vertexArray.getBounds();
	originPos.x = bounds.width * ((int)origin % 3) * 0.5f;
	originPos.y = bounds.height * ((int)origin / 3) * 0.5f;

	sf::Vector2f diff = prevOrigin - originPos; //기존-변경으로 변화량 구하기
	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += diff; //모든 정점마다 변화량 더해주기
	}
}

void VertexArrayGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);

	sf::Vector2f prevOrigin = originPos;
	originPos.x = x;
	originPos.y = y;

	sf::Vector2f delta = prevOrigin - originPos;
	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += delta;
	}
}
