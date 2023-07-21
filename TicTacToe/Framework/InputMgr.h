#pragma once
#include "Singleton.h"

class InputMgr : public Singleton<InputMgr>
{
	friend Singleton<InputMgr>;

protected:
	InputMgr();
	virtual ~InputMgr() override = default;

	std::list<int> downList;
	std::list<int> upList;
	std::list<int> ingList;

	sf::Vector2f mousePos;

public:
	void Update(float dt);
	void UpdateEvent(const sf::Event& ev);

	// Keyboard 입력
	bool GetKeyDown(sf::Keyboard::Key key);
	bool GetKey(sf::Keyboard::Key key);
	bool GetKeyUp(sf::Keyboard::Key key);

	// Mouse 입력
	sf::Vector2f& GetMousePos();
	bool GetMouseButtonDown(sf::Mouse::Button button);
	bool GetMouseButton(sf::Mouse::Button button);
	bool GetMouseButtonUp(sf::Mouse::Button button);
};

#define INPUT_MGR (InputMgr::Instance())
