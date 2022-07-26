#include "MapChip.h"

void MapChip::Initialize()
{
	modelMapWall = Model::CreateFromObject("untitled", false);
	for (int x = 0; x < 13; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			objMapWall[y][x] = Object3d::Create(modelMapWall);
			objMapWall[y][x]->SetScale(XMFLOAT3({ 4, 4, 4 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * 16.0f - (13 * 16.0f / 2), 0.0f, y * 16.0f - (15 * 16.0f / 2) }));

		}
	}
}

void MapChip::Update()
{
	for (int x = 0; x < 13; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			objMapWall[y][x]->Update();
		}
	}
}

int MapChip::ArrayValue(float x, float y)
{
	int mapY = (y / 16) + 8;
	int mapX = (x / 16) + 7;
	
	return mapWall[mapY][mapX];
}

void MapChip::Draw()
{
	for (int x = 0; x < 13; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			if (mapWall[y][x] == 1)
			{
				objMapWall[y][x]->Draw();
			}
		}
	}
}
