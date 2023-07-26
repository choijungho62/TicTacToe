#pragma once
#include "Singleton.h"
//singleton ���� ���, �̰��� �⺻ Ʋ
class Framework :public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:
	Framework() = default;
	Framework(int w, int h, const std::string& t);
	virtual ~Framework() override = default;

	sf::RenderWindow window; //ȭ��
	sf::Clock clock; //�ð�

	int screenWidth = 450;
	int screenHeight = 350;
	std::string title = "Tic Tac Toe!";


public:
	//ȭ���� ���� ����, Ÿ��Ʋ ȭ�鿡 �� �� ���ڷ� ����
	virtual void Init(int width, int height, const std::string& title);
	virtual void Release();

	virtual void Update(float dt);
	virtual void Draw();
	virtual void Run();//���η��� ����

	sf::Vector2f GetWindowSize();
	sf::RenderWindow& GetWindow();
};
#define FRAMEWORK (Framework::Instance())