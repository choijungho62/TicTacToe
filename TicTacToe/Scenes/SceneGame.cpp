#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Framework.h"
#include "VertexArrayGo.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/tile2.png"));
}

SceneGame::~SceneGame()
{
	Release();
}

void SceneGame::Init()
{
	Release();

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;

	worldView.setSize(windowSize);
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	sf::Vector2f tileWorldSize = { 50.f,50.f };
	sf::Vector2f tileTexSize = { 50.f, 50.f };
	background = CreateBackGround({ 5,5 }, { 50.f,50.f }, { 50.f,50.f }, "graphics/tile2.png");
	AddGo(background);

	for (auto go : gameObjects)
	{
		go->Init();
	}

	background->sortLayer = -1;
	background->SetOrigin(Origins::TL);
	background->SetPosition(0.f, 0.f);

	wallBounds = background->vertexArray.getBounds();
	wallBounds.width -= tileWorldSize.x * 2.f;
	wallBounds.height -= tileWorldSize.y * 2.f;
	wallBounds.left += tileWorldSize.x;
	wallBounds.top += tileWorldSize.y;
}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneGame::Enter()
{
	Scene::Enter();

	worldView.setCenter(0.f, 0.f);
}

void SceneGame::Exit()
{
	Scene::Exit();
}



void SceneGame::Update(float dt)
{
	Scene::Update(dt);

}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

VertexArrayGo* SceneGame::CreateBackGround(sf::Vector2i size, sf::Vector2f tileSize, sf::Vector2f texSize, std::string textureId)
{
	VertexArrayGo* background = new VertexArrayGo(textureId, "background");
	background->vertexArray.setPrimitiveType(sf::Quads);
	background->vertexArray.resize(size.x * size.y * 4);

	sf::Vector2f startPos = { 0,0 }; //시작 좌표
	sf::Vector2f offsets[4] =
	{
		//정점의 좌표
		{0.f, 0.f},
		{tileSize.x, 0.f},
		{tileSize.x, tileSize.y},
		{0.f, tileSize.y}
	}; //정점의 순서, 순서는 레퍼렌스 페이지 참고
	sf::Vector2f texOffsets[4] =
	{
		{0.f, 0.f},
		{texSize.x, 0.f},
		{texSize.x, texSize.y},
		{0.f, texSize.y}
	};
	sf::Vector2f currPos = startPos;

	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			int texIndex = 0;
			if (i != 0 && i != size.y - 1 && j != 0 && j != size.x - 1)
				//외곽이 아닐 때, 윗줄, 아랫줄, 왼쪽, 오른쪽 순서로 외곽 검사
			{
				texIndex = 0;
			}

			int tileIndex = size.x * i + j; //2차원 배열의 인덱스를 1차원 배열 인덱스로 변경
			for (int k = 0; k < 4; k++) //4각형의 정점을 하나씩 도는 for문
			{
				int vertexIndex = tileIndex * 4 + k; //정점의 인덱스
				background->vertexArray[vertexIndex].position = currPos + offsets[k];
				background->vertexArray[vertexIndex].texCoords = texOffsets[k];
				background->vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
			}
			currPos.x += tileSize.x;
		}
		currPos.x = startPos.x;
		currPos.y += tileSize.y;
	}
	return background;
}

void SceneGame::HandleClickEvent(sf::Vector2f clickPosition)
{
	// 타일맵 이미지를 클릭한 위치를 확인하여 해당 타일의 인덱스를 계산
	int tileSize = 50; // 타일의 크기
	int xIndex = static_cast<int>(clickPosition.x / tileSize);
	int yIndex = static_cast<int>(clickPosition.y / tileSize);

	int mapWidth = 5; // 타일맵의 가로 크기 (타일 개수)
	int mapHeight = 5; // 타일맵의 세로 크기 (타일 개수)

	// 클릭한 타일이 타일맵 범위 내에 있는지 확인
	if (xIndex >= 0 && xIndex < mapWidth && yIndex >= 0 && yIndex < mapHeight)
	{
		// 새로운 이미지를 표시하기 위한 텍스처 좌표 설정
		sf::Vector2f texOffsets[4] =
		{
			//정점의 텍스처 좌표, O 표시
			{0.f, 50.f},
			{50.f, 50.f},
			{50.f, 100.f},
			{0.f, 100.f}
		};

		// 클릭한 타일의 인덱스를 계산
		int tileIndex = yIndex * mapWidth + xIndex;

		// 클릭한 타일을 변경
		for (int k = 0; k < 4; k++)
		{
			int vertexIndex = tileIndex * 4 + k;

			// {0.50} , {50. 50}, {0. 100}, {50, 100}
			background->vertexArray[vertexIndex].texCoords = texOffsets[k];
		}
	}
}

VertexArrayGo* SceneGame::GetBackground()
{
	return background;
}
