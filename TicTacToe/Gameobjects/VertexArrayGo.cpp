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
	/*���� �����ǿ��� ������ ������ ������ ���� ���ϸ� ��ȭ���� �� �� ����.
	�� ��ȭ���� �� ������ �������ָ� �������� �����.*/
	sf::Vector2f delta = p - position; //��ȭ��
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

	/*prevOrigin: ������ ������, originPosition: ������ ������*/
	sf::Vector2f prevOrigin = originPos;
	sf::FloatRect bounds = vertexArray.getBounds();
	originPos.x = bounds.width * ((int)origin % 3) * 0.5f;
	originPos.y = bounds.height * ((int)origin / 3) * 0.5f;

	sf::Vector2f diff = prevOrigin - originPos; //����-�������� ��ȭ�� ���ϱ�
	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += diff; //��� �������� ��ȭ�� �����ֱ�
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
