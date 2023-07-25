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

	// tileStates �迭�� �ʱ�ȭ ��� Ÿ���� ���¸� false�� ����
	tileStates.clear();
	for (int i = 0; i < 5; i++)
	{
		std::vector<bool> row;
		for (int j = 0; j < 5; j++)
		{
			row.push_back(false);
		}
		tileStates.push_back(row);
	}
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

	sf::Vector2f startPos = { 0,0 }; //���� ��ǥ
	sf::Vector2f offsets[4] =
	{
		//������ ��ǥ
		{0.f, 0.f},
		{tileSize.x, 0.f},
		{tileSize.x, tileSize.y},
		{0.f, tileSize.y}
	}; //������ ����, ������ ���۷��� ������ ����
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
				//�ܰ��� �ƴ� ��, ����, �Ʒ���, ����, ������ ������ �ܰ� �˻�
			{
				texIndex = 0;
			}

			int tileIndex = size.x * i + j; //2���� �迭�� �ε����� 1���� �迭 �ε����� ����
			for (int k = 0; k < 4; k++) //4������ ������ �ϳ��� ���� for��
			{
				int vertexIndex = tileIndex * 4 + k; //������ �ε���
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
	// Ÿ�ϸ� �̹����� Ŭ���� ��ġ�� Ȯ���Ͽ� �ش� Ÿ���� �ε����� ���

	int tileSize = 50; // Ÿ��(�̹���)�� ũ��
	int xIndex = static_cast<int>(clickPosition.x / tileSize);
	int yIndex = static_cast<int>(clickPosition.y / tileSize);

	int mapWidth = 5; // Ÿ�ϸ��� ���� ũ�� (Ÿ�� ����)
	int mapHeight = 5; // Ÿ�ϸ��� ���� ũ�� (Ÿ�� ����)

	// Ŭ���� Ÿ���� Ÿ�ϸ� ���� ���� �ִ��� Ȯ��
	if (xIndex >= 0 && xIndex < mapWidth && yIndex >= 0 && yIndex < mapHeight)
	{
		// Ŭ���� Ÿ���� �̹� Ŭ���� �������� �˻�
		if (!tileStates[yIndex][xIndex])
		{
			// Ŭ���� Ÿ���� ���¸� ����
			tileStates[yIndex][xIndex] = true;

			// �÷��̾� ���ʿ� ���� ǥ���� �̹����� �����մϴ�.
			sf::Vector2f texOffsets[4];
			if (playerOneTurn) // 1P�� ������ ���
			{
				// �÷��̾� 1P�� "X" ǥ�� �̹���
				texOffsets[0] = { 0.f, 100.f };
				texOffsets[1] = { 50.f, 100.f };
				texOffsets[2] = { 50.f, 150.f };
				texOffsets[3] = { 0.f, 150.f };
			}
			else // 2P�� ������ ���
			{
				// �÷��̾� 2P�� "O" ǥ�� �̹���
				texOffsets[0] = { 0.f, 50.f };
				texOffsets[1] = { 50.f, 50.f };
				texOffsets[2] = { 50.f, 100.f };
				texOffsets[3] = { 0.f, 100.f };
			}

			// Ŭ���� Ÿ���� �ε����� ���
			int tileIndex = yIndex * mapWidth + xIndex;

			// Ŭ���� Ÿ���� ����
			for (int k = 0; k < 4; k++)
			{
				int vertexIndex = tileIndex * 4 + k;

				background->vertexArray[vertexIndex].texCoords = texOffsets[k];
			}

			// ���ʸ� �����Ͽ� 1P�� 2P�� �����ư��鼭 Ŭ���� �� �ֵ��� ��
			playerOneTurn = !playerOneTurn;
		}
	}
}

VertexArrayGo* SceneGame::GetBackground()
{
	return background;
}
