#include "MapChip.h"
#include "Collision.h"
#include<time.h>
#include<random>
#include "Input.h"
MapChip::~MapChip()
{
	//safe_delete(modelMapWall);
	//for (int x = 0; x < MapValue; x++)
	//{
	//	for (int y = 0; y < MapValue; y++)
	//	{
	//		safe_delete(objMapWall[y][x]);
	//	}
	//}
	//safe_delete(modelCeiling);
	//for (int x = 0; x < MapValue; x++)
	//{
	//	for (int y = 0; y < MapValue; y++)
	//	{
	//		safe_delete(objCeiling[y][x]);
	//	}
	//}
	//safe_delete(modelFloor);
	//for (int x = 0; x < MapValue; x++)
	//{
	//	for (int y = 0; y < MapValue; y++)
	//	{
	//		safe_delete(objFloor[y][x]);
	//	}
	//}
	//safe_delete(modelCrystal);
	//safe_delete(modelItemCrystal);
	//for (int i = 0; i < 11; i++)
	//{
	//	safe_delete(objCrystal[i]);	
	//}
	//for (int x = 0; x < MapValue; x++)
	//{
	//	for (int y = 0; y < MapValue; y++)
	//	{
	//		safe_delete(spriteMapWall[y][x]);
	//	}
	//}
	//safe_delete(spriteMapBack);
	//safe_delete(spriteMapFrame);
	//for (int i = 0; i < 11; i++)
	//{
	//	safe_delete(spriteCrystal[i]);
	//}
	//for (int i = 0; i < 10; i++)
	//{
	//	safe_delete(spriteNumberNum1[i]);
	//	safe_delete(spriteNumberNum10[i]);
	//}
}

void MapChip::Initialize()
{
	modelMapWall = std::unique_ptr<Model>(Model::CreateFromObject("wall", false));
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objMapWall[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelMapWall.get()));
			objMapWall[y][x]->SetScale(XMFLOAT3({ 4.05f, 4.05f, 4.05f }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * wallSize - (MapValue * wallSize / 2), -2.0f, y * wallSize - (MapValue * wallSize / 2) }));

		}
	}

	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			spriteMapWall[y][x] = nullptr;
		}
	}

	modelCeiling = std::unique_ptr<Model>(Model::CreateFromObject("ceiling", false));
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objCeiling[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelCeiling.get()));
			objCeiling[y][x]->SetScale(XMFLOAT3({ 4.05f, 4.05f, 4.05f }));
			objCeiling[y][x]->SetPosition(XMFLOAT3({ x * wallSize - (MapValue * wallSize / 2), 2.0f, y * wallSize - (MapValue * wallSize / 2) }));
			
		}
	}

	modelFloor = std::unique_ptr<Model>(Model::CreateFromObject("floor", false));
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objFloor[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelFloor.get()));
			objFloor[y][x]->SetScale(XMFLOAT3({ 4.05f, 4.05f, 4.05f }));
			objFloor[y][x]->SetPosition(XMFLOAT3({ x * wallSize - (MapValue * wallSize / 2), 0.5f, y * wallSize - (MapValue * wallSize / 2) }));

		}
	}

	modelCrystal = std::unique_ptr<Model>(Model::CreateFromObject("crystal", false));
	modelItemCrystal = std::unique_ptr<Model>(Model::CreateFromObject("itemCrystal", false));
	for (int i = 0; i < 11; i++)
	{
		objCrystal[i] = std::unique_ptr<Object3d>(Object3d::Create(modelCrystal.get()));
		objCrystal[i]->SetScale(XMFLOAT3({ 0.75f, 0.75f, 0.75f }));
		crystalGetFlag[i] = false;
	}
	objCrystal[3] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal.get()));
	objCrystal[5] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal.get()));

	objCrystal[0]->SetPosition(crystalPos[0]);
	objCrystal[1]->SetPosition(crystalPos[1]);
	objCrystal[2]->SetPosition(crystalPos[2]);
	objCrystal[3]->SetPosition(crystalPos[3]);
	objCrystal[4]->SetPosition(crystalPos[4]);
	objCrystal[5]->SetPosition(crystalPos[5]);
	objCrystal[6]->SetPosition(crystalPos[6]);
	objCrystal[7]->SetPosition(crystalPos[7]);
	objCrystal[8]->SetPosition(crystalPos[8]);
	objCrystal[9]->SetPosition(crystalPos[9]);
	objCrystal[10]->SetPosition(crystalPos[10]);
	
	allGetFlag = false;
	if (!Sprite::LoadTexture(2, L"Resources/mapWall.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(5, L"Resources/miniMapBack.png")) {
		assert(0);
		return;
	}

	if (!Sprite::LoadTexture(7, L"Resources/crystal.png")) {
		assert(0);
		return;
	}

	if (!Sprite::LoadTexture(8, L"Resources/number/1.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(9, L"Resources/number/2.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(10, L"Resources/number/3.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(11, L"Resources/number/4.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(12, L"Resources/number/5.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(13, L"Resources/number/6.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(14, L"Resources/number/7.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(15, L"Resources/number/8.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(16, L"Resources/number/9.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(29, L"Resources/number/0.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(17, L"Resources/crystal2.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(26, L"Resources/miniMapFrame.png")) {
		assert(0);
		return;
	}
	spriteNumberNum1[0] = std::unique_ptr<Sprite>(Sprite::Create(8, { 260 - 10, 656 - 16 - 96 }));
	spriteNumberNum1[1] = std::unique_ptr<Sprite>(Sprite::Create(9, { 260 - 10, 656 - 16 - 96 }));
	spriteNumberNum1[2] = std::unique_ptr<Sprite>(Sprite::Create(10, { 260 - 10, 656 - 16 - 96 }));
	spriteNumberNum1[3] = std::unique_ptr<Sprite>(Sprite::Create(11, { 260 - 10, 656 - 16 - 96 }));
	spriteNumberNum1[4] = std::unique_ptr<Sprite>(Sprite::Create(12, { 260 - 10, 656 - 16 - 96 }));
	spriteNumberNum1[5] = std::unique_ptr<Sprite>(Sprite::Create(13, { 260 - 10, 656 - 16 - 96 }));
	spriteNumberNum1[6] = std::unique_ptr<Sprite>(Sprite::Create(14, { 260 - 10, 656 - 16 - 96 }));
	spriteNumberNum1[7] = std::unique_ptr<Sprite>(Sprite::Create(15, { 260 - 10, 656 - 16 - 96 }));
	spriteNumberNum1[8] = std::unique_ptr<Sprite>(Sprite::Create(16, { 260 - 10, 656 - 16 - 96 }));
	spriteNumberNum1[9] = std::unique_ptr<Sprite>(Sprite::Create(29, { 260 - 10, 656 - 16 - 96 }));

	spriteNumberNum10[0] = std::unique_ptr<Sprite>(Sprite::Create(8, { 260 - 58, 656 - 16 - 96 }));
	spriteNumberNum10[1] = std::unique_ptr<Sprite>(Sprite::Create(9, { 260 - 58, 656 - 16 - 96 }));
	spriteNumberNum10[2] = std::unique_ptr<Sprite>(Sprite::Create(10, { 260 - 58, 656 - 16 - 96 }));
	spriteNumberNum10[3] = std::unique_ptr<Sprite>(Sprite::Create(11, { 260 - 58, 656 - 16 - 96 }));
	spriteNumberNum10[4] = std::unique_ptr<Sprite>(Sprite::Create(12, { 260 - 58, 656 - 16 - 96 }));
	spriteNumberNum10[5] = std::unique_ptr<Sprite>(Sprite::Create(13, { 260 - 58, 656 - 16 - 96 }));
	spriteNumberNum10[6] = std::unique_ptr<Sprite>(Sprite::Create(14, { 260 - 58, 656 - 16 - 96 }));
	spriteNumberNum10[7] = std::unique_ptr<Sprite>(Sprite::Create(15, { 260 - 58, 656 - 16 - 96 }));
	spriteNumberNum10[8] = std::unique_ptr<Sprite>(Sprite::Create(16, { 260 - 58, 656 - 16 - 96 }));
	spriteNumberNum10[9] = std::unique_ptr<Sprite>(Sprite::Create(29, { 260 - 58, 656 - 16 - 96 }));

	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			spriteMapWall[y][x] = std::unique_ptr<Sprite>(Sprite::Create(2, {-16 + 100 + (16.0f * (MapValue - x)),650 + (16.0f * y )}));
		}
	}
	spriteMapBack =  std::unique_ptr<Sprite>(Sprite::Create(5, {-16 + 100,650 -16 - 96}));
	spriteMapFrame = std::unique_ptr<Sprite>(Sprite::Create(26, { -16 + 100,650 - 16 - 96 }));
	
	for (int i = 0; i < 11; i++)
	{
		spriteCrystal[i] = std::unique_ptr<Sprite>(Sprite::Create(7, mapCrystalPos[i]));
	}

	spriteCrystal[3] = std::unique_ptr<Sprite>(Sprite::Create(17, mapCrystalPos[3]));
	spriteCrystal[5] = std::unique_ptr<Sprite>(Sprite::Create(17, mapCrystalPos[5]));

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
			objMapWall[y][x]->SetScale(XMFLOAT3({ 4, 4, 4 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * wallSize - (MapValue * wallSize / 2), 0.0f, y * wallSize - (MapValue * wallSize / 2) }));
		}
	}
	for (int i = 0; i < 11; i++)
	{
		objCrystal[i]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
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
	objCrystal[9]->SetPosition(crystalPos[9]);
	objCrystal[10]->SetPosition(crystalPos[10]);

	allGetFlag = false;
	MapCreate();
	number = 11;
	stopTime = 0;
	displayTime = 0;
	displayFlag = false;

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
			num = 1;
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
	//for (int x = 0; x < MapValue; x++)
	//{
	//	for (int y = 0; y < MapValue; y++)
	//	{
	//		for (int i = 0; i < 49; i++)
	//		{
	//			objMapWall[y][x]->SetLightActive(0, i);
	//		}
	//	}
	//}
}

void MapChip::MapMove(XMFLOAT2 mapPos)
{
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			spriteMapWall[y][x]->SetPosition({ mapPos.x - 16 + 100 + (16 * (MapValue - x)), mapPos.y + 650 + (16 * y) });
		}
	}

	for (int i = 0; i < 11; i++)
	{
		spriteCrystal[i]->SetPosition({ mapPos.x + mapCrystalPos[i].x, mapPos.y + mapCrystalPos[i].y });
	}

	spriteCrystal[3]->SetPosition({ mapPos.x + mapCrystalPos[3].x, mapPos.y + mapCrystalPos[3].y });
	spriteCrystal[5]->SetPosition({ mapPos.x + mapCrystalPos[5].x, mapPos.y + mapCrystalPos[5].y });
}

void MapChip::Update(XMFLOAT3 pos, XMFLOAT2 mapPos, XMFLOAT3 enemyPos)
{
	if (Input::GetInstance()->KeybordPush(DIK_L))
	{
		for (int x = 0; x < MapValue; x++)
		{
			for (int y = 0; y < MapValue; y++)
			{
				objMapWall[y][x]->SetLightAllActive();
			}
		}
	}
	if (Input::GetInstance()->KeybordPush(DIK_K))
	{
		for (int x = 0; x < MapValue; x++)
		{
			for (int y = 0; y < MapValue; y++)
			{
				objMapWall[y][x]->SetLightAllNoActive();
			}
		}
	}
	MapMove(mapPos);
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objMapWall[y][x]->Update(enemyPos);
		}
	}
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objCeiling[y][x]->Update(enemyPos);
		}
	}
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objFloor[y][x]->Update(enemyPos);
		}
	}
	XMFLOAT3 playerPos = pos;
	for (int i = 0; i < 11; i++)
	{
		if (crystalGetFlag[i] == false)
		{
			XMFLOAT3 crystalAngle = objCrystal[i]->GetRotation();
			crystalAngle.y++;
			objCrystal[i]->SetRotation(crystalAngle);
			if (crystalGetFlag[i] = Collision::ChenkSphere2Sphere(playerPos, crystalPos[i], 3.25f, 1.0f))
			{
				number--;
			}
		}
		objCrystal[i]->Update(enemyPos);
	}
	if (crystalGetFlag[0] && crystalGetFlag[1] && crystalGetFlag[2] && crystalGetFlag[3] && crystalGetFlag[4] &&
		crystalGetFlag[5] && crystalGetFlag[6] && crystalGetFlag[7] && crystalGetFlag[8] && crystalGetFlag[9] && crystalGetFlag[10])
	{
		allGetFlag = true;
	}
	if (crystalGetFlag[9] == true || crystalGetFlag[10] == true)
	{
		mapWall[8][10] = 1;
		mapWall[10][8] = 1;
	}
	TimeStop();
	EnemyDisplay();
}

int MapChip::ArrayValue(float x, float y)
{
	int mapY = int((y / wallSize) + ((MapValue+1) / 2));
	int mapX = int((x / wallSize) + ((MapValue+1) / 2));
	
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
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			if (mapWall[y][x] != 1)
			{
				objFloor[y][x]->Draw();
			}
		}
	}
	for (int i = 0; i < 11; i++)
	{
		if(crystalGetFlag[i] == false)
		{
			objCrystal[i]->Draw();
		}
	}
}

void MapChip::DrawSprite()
{
	spriteMapBack->Draw();
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			if (mapWall[y][x] == 1 && spriteMapWall[y][x]->GetPosition().x < 420 && spriteMapWall[y][x]->GetPosition().x > 100
				&& spriteMapWall[y][x]->GetPosition().y > 650 && spriteMapWall[y][x]->GetPosition().y < 986)
			{
				spriteMapWall[y][x]->Draw();
			}
		}
	}

	for (int i = 0; i < 11; i++)
	{
		if (crystalGetFlag[i] == false && spriteCrystal[i]->GetPosition().x < 420 && spriteCrystal[i]->GetPosition().x > 100
			&& spriteCrystal[i]->GetPosition().y > 650 && spriteCrystal[i]->GetPosition().y < 970)
		{
			spriteCrystal[i]->Draw();
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (number == i + 1)
		{
			spriteNumberNum1[i]->Draw();
		}
	}
	if (number == 10)
	{
		spriteNumberNum10[0]->Draw();
		spriteNumberNum1[9]->Draw();
	}
	if (number == 11)
	{
		spriteNumberNum1[0]->Draw();
		spriteNumberNum10[0]->Draw();
	}
	spriteMapFrame->Draw();
}

void MapChip::TimeStop()
{
	if (crystalGetFlag[5] && stopTime == 0)
	{
		stopFlag = true;
	}
	if (stopFlag)
	{
		stopTime++;
	}
	if (stopTime > 300)
	{
		stopFlag = false;
	}
}

void MapChip::EnemyDisplay()
{
	if (crystalGetFlag[3] && displayTime == 0)
	{
		displayFlag = true;
	}
	if (displayFlag)
	{
		displayTime++;
	}
	if (displayTime > 600)
	{
		displayFlag = false;
	}
}
