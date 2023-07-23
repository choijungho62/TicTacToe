#include "stdafx.h"
#include "Framework.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

Framework::Framework(int w, int h, const std::string& t)
    :screenWidth(w), screenHeight(h), title(t)
{
}

void Framework::Init(int width, int height, const std::string& title)
{
    window.create(sf::VideoMode(width, height), title); //window 생성

    SCENE_MGR.Init();
}

void Framework::Release()
{
    SCENE_MGR.Release();
}

void Framework::Update(float dt)
{
    SCENE_MGR.Update(dt);
}

void Framework::Draw()
{
    SCENE_MGR.Draw(window);
}

void Framework::Run()
{
    Init(screenWidth, screenHeight, title); //초기화

    clock.restart();
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        INPUT_MGR.Update(dt);

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                SCENE_MGR.GetCurrScene()->Exit(); //종료될 때 현지 씬 정리
                window.close();
                break;

            case sf::Event::GainedFocus:
                break;

            };
            INPUT_MGR.UpdateEvent(event);
        }
        if (window.isOpen())
        {
            Update(dt); //framework의 update 호출

            window.clear();
            Draw();
            window.display();
        }
    }
    Release();
}

sf::Vector2f Framework::GetWindowSize()
{
    return sf::Vector2f(screenWidth, screenHeight);
}

sf::RenderWindow& Framework::GetWindow()
{
    return window;
}
