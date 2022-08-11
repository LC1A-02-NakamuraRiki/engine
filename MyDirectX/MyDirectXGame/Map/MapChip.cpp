#include "MapChip.h"
#include "../collision/Collision.h"

void MapChip::Initialize()
{
	modelMapWall = Model::CreateFromObject("wall", false);
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			objMapWall[y][x] = Object3d::Create(modelMapWall);
			objMapWall[y][x]->SetScale(XMFLOAT3({ 8, 8, 8 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * 16.0f - (15 * 16.0f / 2), 0.0f, y * 16.0f - (15 * 16.0f / 2) }));

		}
	}

	modelCeiling = Model::CreateFromObject("ceiling", false);
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			objCeiling[y][x] = Object3d::Create(modelCeiling);
			objCeiling[y][x]->SetScale(XMFLOAT3({ 8, 8, 8 }));
			objCeiling[y][x]->SetPosition(XMFLOAT3({ x * 16.0f - (15 * 16.0f / 2), 2.0f, y * 16.0f - (15 * 16.0f / 2) }));

		}
	}

	modelCrystal = Model::CreateFromObject("crystal", false);
	modelItemCrystal = Model::CreateFromObject("itemCrystal", false);
	for (int i = 0; i < 9; i++)
	{
		objCrystal[i] = Object3d::Create(modelCrystal);
		objCrystal[i]->SetScale(XMFLOAT3({ 0.75f, 0.75f, 0.75f }));
		crystalGetFlag[i] = false;
	}
	objCrystal[4] = Object3d::Create(modelItemCrystal);
	objCrystal[0]->SetPosition(crystalPos[0]);
	objCrystal[1]->SetPosition(crystalPos[1]);
	objCrystal[2]->SetPosition(crystalPos[2]);
	objCrystal[3]->SetPosition(crystalPos[3]);
	objCrystal[4]->SetPosition(crystalPos[4]);
	objCrystal[5]->SetPosition(crystalPos[5]);
	objCrystal[6]->SetPosition(crystalPos[6]);
	objCrystal[7]->SetPosition(crystalPos[7]);
	objCrystal[8]->SetPosition(crystalPos[8]);
	
	allGetFlag = false;
}

void MapChip::InitializeValue()
{
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			objMapWall[y][x]->SetScale(XMFLOAT3({ 8, 4, 8 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * 16.0f - (15 * 16.0f / 2), 0.0f, y * 16.0f - (15 * 16.0f / 2) }));
		}
	}
	for (int i = 0; i < 9; i++)
	{
		objCrystal[i]->SetScale(XMFLOAT3({ 0.75f, 0.75f, 0.75f }));
		crystalGetFlag[i] = false;
	}
	objCrystal[0]->SetPosition(crystalPos[0]);
	objCrystal[1]->SetPosition(crystalPos[1]);
	objCrystal[2]->SetPosition(crystalPos[2]);
	objCrystal[3]->SetPosition(crystalPos[3]);
	objCrystal[4]->SetPosition(crystalPos[4]);
	objCrystal[5]->SetPosition(crystalPos[5]);
	objCrystal[6]->SetPosition(crystalPos[6]);
	objCrystal[7]->SetPosition(crystalPos[7]);
	objCrystal[8]->SetPosition(crystalPos[8]);

	allGetFlag = false;
}

void MapChip::Update(XMFLOAT3 pos)
{
	
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			objMapWall[y][x]->Update();
		}
	}
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			objCeiling[y][x]->Update();
		}
	}
	XMFLOAT3 playerPos = pos;
	for (int i = 0; i < 9; i++)
	{
		if (crystalGetFlag[i] == false)
		{
			crystalGetFlag[i] = Collision::ChenkSphere2Sphere(playerPos, crystalPos[i], 3.0f, 6.0f);
		}
		objCrystal[i]->Update();
	}
	if (crystalGetFlag[0] && crystalGetFlag[1] && crystalGetFlag[2] && crystalGetFlag[3] && crystalGetFlag[4] &&
		crystalGetFlag[5] && crystalGetFlag[6] && crystalGetFlag[7] && crystalGetFlag[8])
	{
		allGetFlag = true;
	}
	TimeStop();
}

int MapChip::ArrayValue(float x, float y)
{
	int mapY = (y / 16) + 8;
	int mapX = (x / 16) + 8;
	
	return mapWall[mapY][mapX];
}

void MapChip::Draw()
{
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			if (mapWall[y][x] == 1)
			{
				objMapWall[y][x]->Draw();
			}
		}
	}
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			if (mapWall[y][x] != 1)
			{
				objCeiling[y][x]->Draw();
			}
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if(crystalGetFlag[i] == false)
		{
			objCrystal[i]->Draw();
		}
	}
}

void MapChip::TimeStop()
{
	if (crystalGetFlag[4] && stopTime == 0)
	{
		stopFlag = true;
	}
	if (stopFlag)
	{
		stopTime++;
	}
	if (stopTime > 80)
	{
		stopFlag = false;
	}
}
