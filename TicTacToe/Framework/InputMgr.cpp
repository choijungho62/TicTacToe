#include "stdafx.h"
#include "InputMgr.h"
#include "Framework.h"
#include "Utils.h"

InputMgr::InputMgr()
{

}

void InputMgr::Update(float dt)
{
	downList.clear();
	upList.clear();
}

void InputMgr::UpdateEvent(const sf::Event& ev)
{
	int code = sf::Keyboard::KeyCount + ev.mouseButton.button;
	switch (ev.type)
	{
		// Keyboard
	case sf::Event::KeyPressed:
		if (std::find(ingList.begin(), ingList.end(), ev.key.code) == ingList.end())
		{
			downList.push_back(ev.key.code);
			ingList.push_back(ev.key.code);
		}
		break;
	case sf::Event::KeyReleased:
		ingList.remove(ev.key.code);
		upList.push_back(ev.key.code);
		break;

		// Mouse
	case sf::Event::MouseButtonPressed:
		if (std::find(ingList.begin(), ingList.end(), code) == ingList.end())
		{
			downList.push_back(code);
			ingList.push_back(code);
		}
		break;
	case sf::Event::MouseButtonReleased:
		ingList.remove(code);
		upList.push_back(code);
		break;
	}

	mousePos = (sf::Vector2f)sf::Mouse::getPosition(FRAMEWORK.GetWindow());
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return std::find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
	return std::find(ingList.begin(), ingList.end(), key) != ingList.end();
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
	return std::find(upList.begin(), upList.end(), key) != upList.end();
}

sf::Vector2f& InputMgr::GetMousePos()
{
	return mousePos;
}
bool InputMgr::GetMouseButtonDown(sf::Mouse::Button button)
{
	int code = sf::Keyboard::KeyCount + (int)button;

	return std::find(downList.begin(), downList.end(), code) != downList.end();
}
bool InputMgr::GetMouseButton(sf::Mouse::Button button)
{
	int code = sf::Keyboard::KeyCount + (int)button;

	return std::find(ingList.begin(), ingList.end(), code) != ingList.end();
}
bool InputMgr::GetMouseButtonUp(sf::Mouse::Button button)
{
	int code = sf::Keyboard::KeyCount + (int)button;

	return std::find(upList.begin(), upList.end(), code) != upList.end();
}