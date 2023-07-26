#include "stdafx.h"
#include "TextGo.h"
#include "ResourceMgr.h"

TextGo::TextGo(const std::string fontId, const std::string name)
	:GameObject(name), fontId(fontId)
{

}
TextGo::~TextGo()
{

}

void TextGo::Init()
{

}
void TextGo::Reset()
{
	if (RESOURCE_MGR.GetFont(fontId) != nullptr)
	{
		text.setFont(*RESOURCE_MGR.GetFont(fontId));
	}
	SetOrigin(origin);
}
void TextGo::Update(float dt)
{

}
void TextGo::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}

void TextGo::SetPosition(const sf::Vector2f& position)
{
	GameObject::SetPosition(position);
	text.setPosition(position);
}
void TextGo::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
	text.setPosition(this->position);
}
void TextGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);

	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(text, origin);
	}
}
void TextGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	text.setOrigin(x, y);
}