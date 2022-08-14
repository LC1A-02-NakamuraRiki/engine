#include "MapChip.h"
#include "../collision/Collision.h"
#include<time.h>
#include<random>

void MapChip::Initialize()
{
	modelMapWall = Model::CreateFromObject("wall", false);
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objMapWall[y][x] = Object3d::Create(modelMapWall);
			objMapWall[y][x]->SetScale(XMFLOAT3({ 8, 8, 8 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * 16.0f - (MapValue * 16.0f / 2), 0.0f, y * 16.0f - (MapValue * 16.0f / 2) }));

		}
	}

	modelCeiling = Model::CreateFromObject("ceiling", false);
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objCeiling[y][x] = Object3d::Create(modelCeiling);
			objCeiling[y][x]->SetScale(XMFLOAT3({ 8, 8, 8 }));
			objCeiling[y][x]->SetPosition(XMFLOAT3({ x * 16.0f - (MapValue * 16.0f / 2), 2.0f, y * 16.0f - (MapValue * 16.0f / 2) }));

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
	LoadCSV(mapWallLeftUp, "Resources/map/a1.csv");
	LoadCSV(mapWallLeftCenter, "Resources/map/a2.csv");
	LoadCSV(mapWallLeftDown, "Resources/map/a3.csv");
	LoadCSV(mapWallCenterUp, "Resources/map/a4.csv");
	LoadCSV(mapWallCenterCenter, "Resources/map/a5.csv");
	LoadCSV(mapWallCenterDown, "Resources/map/a6.csv");
	LoadCSV(mapWallRightUp, "Resources/map/a7.csv");
	LoadCSV(mapWallRightCenter, "Resources/map/a8.csv");
	LoadCSV(mapWallRightDown, "Resources/map/a9.csv");

	LoadCSV(      mapWallLeftUp1,"Resources/map/b1.csv");
	LoadCSV(  mapWallLeftCenter1,"Resources/map/b2.csv");
	LoadCSV(    mapWallLeftDown1,"Resources/map/b3.csv");
	LoadCSV(    mapWallCenterUp1,"Resources/map/b4.csv");
	LoadCSV(mapWallCenterCenter1,"Resources/map/b5.csv");
	LoadCSV(  mapWallCenterDown1,"Resources/map/b6.csv");
	LoadCSV(     mapWallRightUp1,"Resources/map/b7.csv");
	LoadCSV( mapWallRightCenter1,"Resources/map/b8.csv");
	LoadCSV(   mapWallRightDown1,"Resources/map/b9.csv");

}

void MapChip::InitializeValue()
{
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objMapWall[y][x]->SetScale(XMFLOAT3({ 8, 4, 8 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * 16.0f - (MapValue * 16.0f / 2), 0.0f, y * 16.0f - (MapValue * 16.0f / 2) }));
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
	MapCreate();
}

void MapChip::MapCreate()
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<>rand3(0, 1);//0~3‚Ì”ÍˆÍ
	int num = rand3(mt);

	for (int z = 0; z < MapValue / 3; z++)
	{
		for (int x = 0; x < MapValue / 3; x++)
		{
			if (num == 0)
			{
				mapWall[z][x] = mapWallLeftUp[z][x];
			}
			else if (num == 1)
			{
				mapWall[z][x] = mapWallLeftUp1[z][x];
			}
			else if (num == 2)
			{
				mapWall[z][x] = mapWallLeftUp[z][x];
			}
		}
	}
	num = rand3(mt);
	for (int z = 0; z < MapValue / 3; z++)
	{
		for (int x = 0; x < MapValue / 3; x++)
		{
			if (num == 0)
			{
				mapWall[z + MapValue / 3][x] = mapWallLeftCenter[z][x];
			}
			else if (num == 1)
			{
				mapWall[z + MapValue / 3][x] = mapWallLeftCenter1[z][x];
			}
			else if (num == 2)
			{
				mapWall[z + MapValue / 3][x] = mapWallLeftCenter[z][x];
			}
		}
	}
	num = rand3(mt);
	for (int z = 0; z < MapValue / 3; z++)
	{
		for (int x = 0; x < MapValue / 3; x++)
		{
			if (num == 0)
			{
				mapWall[z + (MapValue / 3) * 2][x] = mapWallLeftDown[z][x];
			}
			else if (num == 1)
			{
				mapWall[z + (MapValue / 3) * 2][x] = mapWallLeftDown1[z][x];
			}
			else if (num == 2)
			{
				mapWall[z + (MapValue / 3) * 2][x] = mapWallLeftDown[z][x];
			}
		}
	}

	num = rand3(mt);
	for (int z = 0; z < MapValue / 3; z++)
	{
		for (int x = 0; x < MapValue / 3; x++)
		{
			if (num == 0)
			{
				mapWall[z][x + MapValue / 3] = mapWallCenterUp[z][x];
			}
			else if (num == 1)
			{
				mapWall[z][x + MapValue / 3] = mapWallCenterUp1[z][x];
			}
			else if (num == 2)
			{
				mapWall[z][x + MapValue / 3] = mapWallCenterUp[z][x];
			}
		}
	}
	num = rand3(mt);
	for (int z = 0; z < MapValue / 3; z++)
	{
		for (int x = 0; x < MapValue / 3; x++)
		{
			if (num == 0)
			{
				mapWall[z + MapValue / 3][x + MapValue / 3] = mapWallCenterCenter[z][x];
			}
			else if (num == 1)
			{
				mapWall[z + MapValue / 3][x + MapValue / 3] = mapWallCenterCenter1[z][x];
			}
			else if (num == 2)
			{
				mapWall[z + MapValue / 3][x + MapValue / 3] = mapWallCenterCenter[z][x];
			}
		}
	}
	num = rand3(mt);
	for (int z = 0; z < MapValue / 3; z++)
	{
		for (int x = 0; x < MapValue / 3; x++)
		{
			if (num == 0)
			{
				mapWall[z + (MapValue / 3) * 2][x + MapValue / 3] = mapWallCenterDown[z][x];
			}
			else if (num == 1)
			{
				mapWall[z + (MapValue / 3) * 2][x + MapValue / 3] = mapWallCenterDown1[z][x];
			}
			else if (num == 2)
			{
				mapWall[z + (MapValue / 3) * 2][x + MapValue / 3] = mapWallCenterDown[z][x];
			}
		}
	}

	num = rand3(mt);
	for (int z = 0; z < MapValue / 3; z++)
	{
		for (int x = 0; x < MapValue / 3; x++)
		{
			if (num == 0)
			{
				mapWall[z][x + (MapValue / 3) * 2] = mapWallRightUp[z][x];
			}
			else if (num == 1)
			{
				mapWall[z][x + (MapValue / 3) * 2] = mapWallRightUp1[z][x];
			}
			else if (num == 2)
			{
				mapWall[z][x + (MapValue / 3) * 2] = mapWallRightUp[z][x];
			}
		}
	}
	num = rand3(mt);
	for (int z = 0; z < MapValue / 3; z++)
	{
		for (int x = 0; x < MapValue / 3; x++)
		{
			if (num == 0)
			{
				mapWall[z + MapValue / 3][x + (MapValue / 3) * 2] = mapWallRightCenter[z][x];
			}
			else if (num == 1)
			{
				mapWall[z + MapValue / 3][x + (MapValue / 3) * 2] = mapWallRightCenter1[z][x];
			}
			else if (num == 2)
			{
				mapWall[z + MapValue / 3][x + (MapValue / 3) * 2] = mapWallRightCenter[z][x];
			}
		}
	}
	num = rand3(mt);
	for (int z = 0; z < MapValue / 3; z++)
	{
		for (int x = 0; x < MapValue / 3; x++)
		{
			if (num == 0)
			{
				mapWall[z + (MapValue / 3) * 2][x + (MapValue / 3) * 2] = mapWallRightDown[z][x];
			}
			else if (num == 1)
			{
				mapWall[z + (MapValue / 3) * 2][x + (MapValue / 3) * 2] = mapWallRightDown1[z][x];
			}
			else if (num == 2)
			{
				mapWall[z + (MapValue / 3) * 2][x + (MapValue / 3) * 2] = mapWallRightDown[z][x];
			}
		}
	}
}

void MapChip::Update(XMFLOAT3 pos)
{
	
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objMapWall[y][x]->Update();
		}
	}
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
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
	int mapY = (y / 16) + ((MapValue+1) / 2);
	int mapX = (x / 16) + ((MapValue+1) / 2);
	
	return mapWall[mapY][mapX];
}

void MapChip::Draw()
{
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			if (mapWall[y][x] == 1)
			{
				objMapWall[y][x]->Draw();
			}
		}
	}
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
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
	if (stopTime > 180)
	{
		stopFlag = false;
	}
}
