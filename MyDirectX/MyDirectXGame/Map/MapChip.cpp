#include "MapChip.h"

void MapChip::Initialize()
{
	modelMapWall = Model::CreateFromObject("untitled", false);
	for (int x = 0; x < 19; x++)
	{
		for (int y = 0; y < 19; y++)
		{
			objMapWall[y][x] = Object3d::Create(modelMapWall);
			objMapWall[y][x]->SetScale(XMFLOAT3({ 2, 2, 2 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * 8.0f - (19 * 8.0f / 2), 0.0f, y * 8.0f - (19 * 8.0f / 2) }));

		}
	}
}

void MapChip::Update()
{
	for (int x = 0; x < 19; x++)
	{
		for (int y = 0; y < 19; y++)
		{
			objMapWall[y][x]->Update();
		}
	}
}

int MapChip::ArrayValue(float x, float y)
{
	int mapY = (y / 8) + 10;
	int mapX = (x / 8) + 10;
	
	return mapWall[mapY][mapX];
}

void MapChip::Draw()
{
	for (int x = 0; x < 19; x++)
	{
		for (int y = 0; y < 19; y++)
		{
			if (mapWall[y][x] == 1)
			{
				objMapWall[y][x]->Draw();
			}
		}
	}
}
