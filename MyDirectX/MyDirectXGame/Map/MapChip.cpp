#include "MapChip.h"
#include "Collision.h"
#include<time.h>
#include<random>
#include "Input.h"
MapChip::~MapChip()
{
}

void MapChip::Initialize()
{
	//���f���ǂݍ���
	modelPictureFrame = std::unique_ptr<Model>(Model::CreateFromObject("pictureFrame", false));
	modelDesk = std::unique_ptr<Model>(Model::CreateFromObject("desk", false));
	modelMapWall = std::unique_ptr<Model>(Model::CreateFromObject("wall", false));
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objPictureFrame1[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelPictureFrame.get()));
			objPictureFrame1[y][x]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
			objPictureFrame1[y][x]->SetPosition(XMFLOAT3({ 80.0f - (x * 8.0f),4.25f,76.0f - (y *8.0f)}));

			objDesk1[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelDesk.get()));
			objDesk1[y][x]->SetScale(XMFLOAT3({ 0.02f, 0.065f, 0.05f }));
			objDesk1[y][x]->SetPosition(XMFLOAT3({ +0.5f + 80.0f - (x * 8.0f),2.0f,76.0f - (y * 8.0f) }));

			objPictureFrame2[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelPictureFrame.get()));
			objPictureFrame2[y][x]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
			objPictureFrame2[y][x]->SetPosition(XMFLOAT3({ 72.0f - (x * 8.0f),4.25f,76.0f - (y * 8.0f) }));

			objDesk2[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelDesk.get()));
			objDesk2[y][x]->SetScale(XMFLOAT3({ 0.02f, 0.065f, 0.05f }));
			objDesk2[y][x]->SetPosition(XMFLOAT3({ -0.5f + 72.0f - (x * 8.0f),2.0f,76.0f - (y * 8.0f) }));

			objPictureFrame3[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelPictureFrame.get()));
			objPictureFrame3[y][x]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
			objPictureFrame3[y][x]->SetPosition(XMFLOAT3({ 76.0f - (x * 8.0f),4.25f,72.0f - (y * 8.0f) }));
			objPictureFrame3[y][x]->SetRotation(XMFLOAT3({ 0.0f, 90.0f, 0.0f }));

			objDesk3[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelDesk.get()));
			objDesk3[y][x]->SetScale(XMFLOAT3({ 0.02f, 0.065f, 0.05f }));
			objDesk3[y][x]->SetPosition(XMFLOAT3({ 76.0f - (x * 8.0f),2.0f,-0.5f + 72.0f - (y * 8.0f) }));
			objDesk3[y][x]->SetRotation(XMFLOAT3({ 0.0f, 90.0f, 0.0f }));

			objPictureFrame4[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelPictureFrame.get()));
			objPictureFrame4[y][x]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
			objPictureFrame4[y][x]->SetPosition(XMFLOAT3({ 76.0f - (x * 8.0f),4.25f,80.0f - (y * 8.0f) }));
			objPictureFrame4[y][x]->SetRotation(XMFLOAT3({ 0.0f, 90.0f, 0.0f }));

			objDesk4[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelDesk.get()));
			objDesk4[y][x]->SetScale(XMFLOAT3({ 0.02f, 0.065f, 0.05f }));
			objDesk4[y][x]->SetPosition(XMFLOAT3({ 76.0f - (x * 8.0f),2.0f,+0.5f + 80.0f - (y * 8.0f) }));
			objDesk4[y][x]->SetRotation(XMFLOAT3({ 0.0f, 90.0f, 0.0f }));
			
			objMapWall[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelMapWall.get()));
			objMapWall[y][x]->SetScale(XMFLOAT3({ 4.05f, 4.05f, 4.05f }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * wallSize - (MapValue * wallSize / 2), -2.0f, y * wallSize - (MapValue * wallSize / 2) }));

		}
	}
	modelCeiling = std::unique_ptr<Model>(Model::CreateFromObject("ceiling", false));
	modelFlat = std::unique_ptr<Model>(Model::CreateFromObject("roof", false));
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			if (x%3 == 1)
			{
				if (y%3 == 1)
				{
					objCeiling[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelCeiling.get()));
					
				}
				else
				{
					objCeiling[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelFlat.get()));
				}
			}
			else
			{
				objCeiling[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelFlat.get()));
			}
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
			objFloor[y][x]->SetPosition(XMFLOAT3({ x * wallSize - (MapValue * wallSize / 2), -3.8f, y * wallSize - (MapValue * wallSize / 2) }));

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
	for (int i = 0; i < 4; i++)
	{
		modelDoor[i] = std::unique_ptr<Model>(Model::CreateFromObject("door", false));
		objMapDoor[i] = std::unique_ptr<Object3d>(Object3d::Create(modelDoor[i].get()));
		objMapDoor[i]->SetRotation(XMFLOAT3({ 0.0f,doorAngle[i],0.0f}));
		objMapDoor[i]->SetScale(XMFLOAT3({ 1.0f,1.5f,2.0f }));
	}
	objMapDoor[0]->SetPosition(XMFLOAT3({ -0.2f,0.2f,-16.0f }));
	objMapDoor[1]->SetPosition(XMFLOAT3({ -7.8f,0.2f,-16.0f }));
	objMapDoor[2]->SetPosition(XMFLOAT3({ -0.2f,0.2f,8.0f }));
	objMapDoor[3]->SetPosition(XMFLOAT3({ -7.8f,0.2f,8.0f }));
	
	//�摜�ǂݍ���
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			spriteMapWall[y][x] = nullptr;
		}
	}
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
	if (!Sprite::LoadTexture(31, L"Resources/EnemyStop.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(32, L"Resources/EnemySpotted.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(33, L"Resources/MiniMapBack2.png")) {
		assert(0);
		return;
	}

	if (!Sprite::LoadTexture(45, L"Resources/Open.png")) {
		assert(0);
		return;
	}

	//�摜����
	spriteDoorOpen = std::unique_ptr<Sprite>(Sprite::Create(45, { 990, 850 }));
	spriteDoorOpen->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	spriteNumberNum1[0] = std::unique_ptr<Sprite>(Sprite::Create(8,  { 260 - 10, 656 - 16 - 96 }));
	spriteNumberNum1[1] = std::unique_ptr<Sprite>(Sprite::Create(9,  { 260 - 10, 656 - 16 - 96 }));
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

	 spriteEnemyStop = std::unique_ptr<Sprite>(Sprite::Create(31, { 990, 850 }));
	 spriteEnemyStop->SetAnchorPoint(XMFLOAT2(0.5f,0.5f));
	 spriteEnemyStop->SetSize(XMFLOAT2(stopFontSize));

	 spriteEnemySpot = std::unique_ptr<Sprite>(Sprite::Create(32, { 990, 850 }));
	 spriteEnemySpot->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	 spriteEnemySpot->SetSize(XMFLOAT2(spotFontSize));

	 spriteSpotEffect = std::unique_ptr<Sprite>(Sprite::Create(33, { -16 + 100,650 - 16 - 96 }));

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

	//�}�b�v�ǂݍ���
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
	allGetFlag = false;
}

void MapChip::InitializeValue()
{
	//�^�C�g�����̏�����
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
	doorAngle[0] = 90;
	doorAngle[1] = 270;
	doorAngle[2] = 90;
	doorAngle[3] = 270;

	stopFontSize = { 1200.0f * 10, 200.0f * 10 };
	stopSprieteTime = 0;
	stopAlpha = 1.0f;

	spotFontSize = { 1200.0f * 10, 200.0f * 10 };
	spotSprieteTime = 0;
	spotAlpha = 1.0f;

	number = 11;
	gateOpenFlag = false;

	lightAction = 0;
	lightCount = 0; 
}

void MapChip::MapCreate()
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<>rand3(0, 1);//0~3�͈̔�
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

void MapChip::Update(XMFLOAT3 pos, XMFLOAT2 mapPos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3)
{	
	if (gateOpenFlag == true && doorAngle[0] > 0)
	{
		doorAngle[1] += 10;
		doorAngle[0] -= 10;
		doorAngle[3] -= 10;
		doorAngle[2] += 10;
		mapWall[12][10] = 0;
		mapWall[8][10] = 0;

	}
	for (int i = 0; i < 4 ;i++)
	{
		objMapDoor[i]->SetRotation(XMFLOAT3({ 0.0f,doorAngle[i],0.0f}));
	}
	bool lightSilen = LightAction();
	MapMove(mapPos);
	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			int lightFlag = lightSilen;
			if (ArrayValue(68.0f + (-24.0f * (6 - x)), -76.0f + (24.0f * y)) == 1)
			{
				lightFlag = 0;
			}
			objMapWall[0 + 3 * y][0 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objMapWall[0 + 3 * y][1 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objMapWall[0 + 3 * y][2 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objMapWall[1 + 3 * y][0 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objMapWall[1 + 3 * y][1 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objMapWall[1 + 3 * y][2 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objMapWall[2 + 3 * y][0 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objMapWall[2 + 3 * y][1 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objMapWall[2 + 3 * y][2 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
		}
	}
	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			int lightFlag = lightSilen;
			if (ArrayValue(68.0f + (-24.0f * (6 - x)), -76.0f + (24.0f * y)) == 1)
			{
				lightFlag = 0;
			}
			objCeiling[0 + 3 * y][0 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objCeiling[0 + 3 * y][1 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objCeiling[0 + 3 * y][2 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objCeiling[1 + 3 * y][0 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objCeiling[1 + 3 * y][1 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objCeiling[1 + 3 * y][2 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objCeiling[2 + 3 * y][0 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objCeiling[2 + 3 * y][1 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objCeiling[2 + 3 * y][2 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3,XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
		}
	}
	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			int lightFlag = lightSilen;
			if (ArrayValue(68.0f + (-24.0f * (6 - x)), -76.0f + (24.0f * y)) == 1)
			{
				lightFlag = 0;
			}
			objFloor[0 + 3 * y][0 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objFloor[0 + 3 * y][1 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objFloor[0 + 3 * y][2 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objFloor[1 + 3 * y][0 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objFloor[1 + 3 * y][1 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objFloor[1 + 3 * y][2 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objFloor[2 + 3 * y][0 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objFloor[2 + 3 * y][1 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
			objFloor[2 + 3 * y][2 + 3 * x]->Update(enemyPos1, enemyPos2,enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * y)), lightFlag, 0);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		objMapDoor[i]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}
	XMFLOAT3 playerPos = pos;

	int mapY = int((playerPos.z / 8) + ((21 + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((21 + 1) / 2));
	mapPlayer[mapX][mapY] = 1;
	mapPlayer[mapX + 1][mapY] = 0;
	mapPlayer[mapX - 1][mapY] = 0;
	mapPlayer[mapX][mapY + 1] = 0;
	mapPlayer[mapX][mapY - 1] = 0;

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
		objCrystal[i]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}

	for (int x = 0; x < 21; x += 2)
	{
		for (int y = 0; y < 21; y += 2)
		{
			objPictureFrame1[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 80.0f - (x * 8.0f), 4.25f, 76.0f - (y * 8.0f) }), lightSilen, 0);
			objDesk1[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ +0.5f + 80.0f - (x * 8.0f),2.0f,76.0f - (y * 8.0f) }), lightSilen, 0);

			objPictureFrame2[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 72.0f - (x * 8.0f),4.25f,76.0f - (y * 8.0f) }), lightSilen, 0);
			objDesk2[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ -0.5f + 72.0f - (x * 8.0f),2.0f,76.0f - (y * 8.0f) }), lightSilen, 0);

			objPictureFrame3[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 76.0f - (x * 8.0f),4.25f,72.0f - (y * 8.0f) }), lightSilen, 0);
			objDesk3[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 76.0f - (x * 8.0f),2.0f,-0.5f + 72.0f - (y * 8.0f) }), lightSilen, 0);

			objPictureFrame4[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 76.0f - (x * 8.0f),4.25f,80.0f - (y * 8.0f) }), lightSilen, 0);
			objDesk4[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 76.0f - (x * 8.0f),2.0f,+0.5f + 80.0f - (y * 8.0f) }), lightSilen, 0);
		}
	}
	if (crystalGetFlag[0] && crystalGetFlag[1] && crystalGetFlag[2] && crystalGetFlag[3] && crystalGetFlag[4] &&
		crystalGetFlag[5] && crystalGetFlag[6] && crystalGetFlag[7] && crystalGetFlag[8] && crystalGetFlag[9] && crystalGetFlag[10])
	{
		allGetFlag = true;
	}
	TimeStop();
	EnemyDisplay();

	if (number >= 10)
	{
		spriteNumberNum1[0]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		spriteNumberNum1[1]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		spriteNumberNum1[2]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		spriteNumberNum1[3]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		spriteNumberNum1[4]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		spriteNumberNum1[5]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		spriteNumberNum1[6]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		spriteNumberNum1[7]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		spriteNumberNum1[8]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		spriteNumberNum1[9]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
	}
	else
	{
		spriteNumberNum1[0]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
		spriteNumberNum1[1]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
		spriteNumberNum1[2]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
		spriteNumberNum1[3]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
		spriteNumberNum1[4]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
		spriteNumberNum1[5]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
		spriteNumberNum1[6]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
		spriteNumberNum1[7]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
		spriteNumberNum1[8]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
		spriteNumberNum1[9]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
	}
	if (Input::GetInstance()->KeybordTrigger(DIK_E) && mapX == 10 && mapY == 9)
	{
		gateOpenFlag = true;
	}
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
	for (int i = 0; i < 4; i++)
	{
		objMapDoor[i]->Draw();
	}
	for (int x = 0; x < 21; x+=2)
	{
		for (int y = 0; y < 21; y+=2)
		{
			if (mapWall[y][x] == 1)
			{
				objPictureFrame1[y][x]->Draw();
				objDesk1[y][x]->Draw();

				objPictureFrame2[y][x]->Draw();
				objDesk2[y][x]->Draw();

				objPictureFrame3[y][x]->Draw();
				objDesk3[y][x]->Draw();

				objPictureFrame4[y][x]->Draw();
				objDesk4[y][x]->Draw();
			}
		}
	}
}

void MapChip::DrawSprite(XMFLOAT3 pos)
{
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((21 + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((21 + 1) / 2));
	if (!displayFlag)
	{
		spriteMapBack->Draw(1.0f);
	}
	else
	{
		spriteSpotEffect->Draw(1.0f);
	}

	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			if (mapWall[y][x] == 1 && spriteMapWall[y][x]->GetPosition().x < 420 && spriteMapWall[y][x]->GetPosition().x > 100
				&& spriteMapWall[y][x]->GetPosition().y > 650 && spriteMapWall[y][x]->GetPosition().y < 986)
			{
				spriteMapWall[y][x]->Draw(1.0f);
			}
		}
	}

	for (int i = 0; i < 11; i++)
	{
		if (crystalGetFlag[i] == false && spriteCrystal[i]->GetPosition().x < 420 && spriteCrystal[i]->GetPosition().x > 100
			&& spriteCrystal[i]->GetPosition().y > 650 && spriteCrystal[i]->GetPosition().y < 986)
		{
			spriteCrystal[i]->Draw(1.0f);
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (number == i + 1)
		{
			spriteNumberNum1[i]->Draw(1.0f);
		}
	}
	if (number == 10)
	{
		spriteNumberNum10[0]->Draw(1.0f);
		spriteNumberNum1[9]->Draw(1.0f);
	}
	if (number == 11)
	{
		spriteNumberNum1[0]->Draw(1.0f);
		spriteNumberNum10[0]->Draw(1.0f);
	}
	spriteMapFrame->Draw(1.0f);
	
	
	if (spotSprieteTime < 80 && displayFlag)
	{	
		spotSprieteTime++;
		spriteEnemySpot->Draw(spotAlpha);
	}
	if (spotSprieteTime > 60 && spotSprieteTime < 80 && displayFlag)
	{
		spotAlpha -= 0.05f;
	}
	if (spotSprieteTime < 60 && spotFontSize.x > 1200 && displayFlag)
	{
		spotFontSize.x -= 1200;
		spotFontSize.y -= 200;
		spriteEnemySpot->SetSize(spotFontSize);
	}
	
	if (stopSprieteTime < 80 && stopFlag)
	{
		stopSprieteTime++;
		spriteEnemyStop->Draw(stopAlpha);
	}
	if (stopSprieteTime > 60 && stopSprieteTime < 80 && stopFlag)
	{
		stopAlpha -= 0.05f;
	}
	if (stopSprieteTime < 60 && stopFontSize.x > 1200 && stopFlag)
	{
		stopFontSize.x -= 1200;
		stopFontSize.y -= 200;
		spriteEnemyStop->SetSize(stopFontSize);
	}
	if (gateOpenFlag == false && mapX == 10 && mapY == 9)
	{
		spriteDoorOpen->Draw(1.0f);
	}
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

bool MapChip::LightAction()
{
	if (lightAction)
	{
		lightCount++;
		if (lightCount > 300)
		{
			lightCount = 0;
		}
		else if (lightCount > 90)
		{
			return 1;
		}
		else if (lightCount > 80)
		{
			return 1;
		}
		else if (lightCount > 60)
		{
			return 0;
		}
		else if (lightCount > 40)
		{
			return 1;
		}
		else if (lightCount > 20)
		{
			return 0;
		}
		return 1;
	}
	else
	{
		return 1;
	}
}
