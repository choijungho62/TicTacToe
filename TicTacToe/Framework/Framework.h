#pragma once
#include "Singleton.h"
//singleton 적용 방법, 이것이 기본 틀
class Framework :public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:
	Framework() = default;
	Framework(int w, int h, const std::string& t);
	virtual ~Framework() override = default;

	sf::RenderWindow window; //화면
	sf::Clock clock; //시간

	int screenWidth = 450;
	int screenHeight = 350;
	std::string title = "Tic Tac Toe!";


public:
	//화면의 가로 세로, 타이틀 화면에 뜰 글 인자로 전달
	virtual void Init(int width, int height, const std::string& title);
	virtual void Release();

	virtual void Update(float dt);
	virtual void Draw();
	virtual void Run();//메인루프 실행

	sf::Vector2f GetWindowSize();
	sf::RenderWindow& GetWindow();
};
#define FRAMEWORK (Framework::Instance())