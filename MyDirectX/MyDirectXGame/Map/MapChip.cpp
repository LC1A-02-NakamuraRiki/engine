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
	//モデル読み込み
	modelPictureFrame = std::unique_ptr<Model>(Model::CreateFromObject("pictureFrame", false));
	modelDesk = std::unique_ptr<Model>(Model::CreateFromObject("desk", false));
	modelMapWall = std::unique_ptr<Model>(Model::CreateFromObject("wall", false));
	for (int x = 0; x < MAPVALUE; x++){
		for (int y = 0; y < MAPVALUE; y++){
			objPictureFrame1[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelPictureFrame.get()));
			objPictureFrame1[y][x]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
			objPictureFrame1[y][x]->SetPosition(XMFLOAT3({ 80.0f - (x * WALLSIZE),4.25f,76.0f - (y * WALLSIZE)}));

			objDesk1[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelDesk.get()));
			objDesk1[y][x]->SetScale(XMFLOAT3({ 0.02f, 0.065f, 0.05f }));
			objDesk1[y][x]->SetPosition(XMFLOAT3({ +0.5f + 80.0f - (x * WALLSIZE),2.0f,76.0f - (y * WALLSIZE) }));

			objPictureFrame2[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelPictureFrame.get()));
			objPictureFrame2[y][x]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
			objPictureFrame2[y][x]->SetPosition(XMFLOAT3({ 72.0f - (x * WALLSIZE),4.25f,76.0f - (y * WALLSIZE) }));

			objDesk2[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelDesk.get()));
			objDesk2[y][x]->SetScale(XMFLOAT3({ 0.02f, 0.065f, 0.05f }));
			objDesk2[y][x]->SetPosition(XMFLOAT3({ -0.5f + 72.0f - (x * WALLSIZE),2.0f,76.0f - (y * WALLSIZE) }));

			objPictureFrame3[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelPictureFrame.get()));
			objPictureFrame3[y][x]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
			objPictureFrame3[y][x]->SetPosition(XMFLOAT3({ 76.0f - (x * WALLSIZE),4.25f,72.0f - (y * WALLSIZE) }));
			objPictureFrame3[y][x]->SetRotation(XMFLOAT3({ 0.0f, 90.0f, 0.0f }));

			objDesk3[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelDesk.get()));
			objDesk3[y][x]->SetScale(XMFLOAT3({ 0.02f, 0.065f, 0.05f }));
			objDesk3[y][x]->SetPosition(XMFLOAT3({ 76.0f - (x * WALLSIZE),2.0f,-0.5f + 72.0f - (y * WALLSIZE) }));
			objDesk3[y][x]->SetRotation(XMFLOAT3({ 0.0f, 90.0f, 0.0f }));

			objPictureFrame4[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelPictureFrame.get()));
			objPictureFrame4[y][x]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
			objPictureFrame4[y][x]->SetPosition(XMFLOAT3({ 76.0f - (x * WALLSIZE),4.25f,80.0f - (y * WALLSIZE) }));
			objPictureFrame4[y][x]->SetRotation(XMFLOAT3({ 0.0f, 90.0f, 0.0f }));

			objDesk4[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelDesk.get()));
			objDesk4[y][x]->SetScale(XMFLOAT3({ 0.02f, 0.065f, 0.05f }));
			objDesk4[y][x]->SetPosition(XMFLOAT3({ 76.0f - (x * WALLSIZE),2.0f,+0.5f + 80.0f - (y * WALLSIZE) }));
			objDesk4[y][x]->SetRotation(XMFLOAT3({ 0.0f, 90.0f, 0.0f }));
			
			objMapWall[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelMapWall.get()));
			objMapWall[y][x]->SetScale(XMFLOAT3({ 4, 4, 4 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 0.0f, y * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }));
		}
	}
	modelCeiling = std::unique_ptr<Model>(Model::CreateFromObject("ceiling", false));
	modelFlat = std::unique_ptr<Model>(Model::CreateFromObject("roof", false));
	for (int x = 0; x < MAPVALUE; x++)
	{
		for (int y = 0; y < MAPVALUE; y++)
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
			objCeiling[y][x]->SetPosition(XMFLOAT3({ x * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 2.0f, y * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }));
		}
	}

	modelFloor = std::unique_ptr<Model>(Model::CreateFromObject("floor", false));
	for (int x = 0; x < MAPVALUE; x++){
		for (int y = 0; y < MAPVALUE; y++){
			objFloor[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelFloor.get()));
			objFloor[y][x]->SetScale(XMFLOAT3({ 4.05f, 4.05f, 4.05f }));
			objFloor[y][x]->SetPosition(XMFLOAT3({ x * WALLSIZE - (MAPVALUE * WALLSIZE / 2), -3.8f, y * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }));

		}
	}
	modelCrystal = std::unique_ptr<Model>(Model::CreateFromObject("crystal", false));
	modelItemCrystal = std::unique_ptr<Model>(Model::CreateFromObject("itemCrystal", false));
	for (int i = 0; i < 11; i++){
		objCrystal[i] = std::unique_ptr<Object3d>(Object3d::Create(modelCrystal.get()));
		objCrystal[i]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
		crystalGetFlag[i] = false;
	}
	objCrystal[3] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal.get()));
	objCrystal[5] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal.get()));
	objCrystal[3]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
	objCrystal[5]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));

	for (int i = 0; i < 11; i++)
	{
		objCrystal[i]->SetPosition(crystalPos[i]);
	}
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
	
	//画像の読み込み
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
	if (!Sprite::LoadTexture(71, L"Resources/number/1.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(72, L"Resources/number/2.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(73, L"Resources/number/3.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(74, L"Resources/number/4.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(75, L"Resources/number/5.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(76, L"Resources/number/6.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(77, L"Resources/number/7.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(78, L"Resources/number/8.png")) {
		assert(0);
		return;
	}if (!Sprite::LoadTexture(79, L"Resources/number/9.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(80, L"Resources/number/0.png")) {
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

	//スプライトの初期化
	for (int x = 0; x < MAPVALUE; x++){
		for (int y = 0; y < MAPVALUE; y++)	{
			spriteMapWall[y][x] = nullptr;
		}
	}
	spriteDoorOpen = std::unique_ptr<Sprite>(Sprite::Create(45, { 990, 850 }));
	spriteDoorOpen->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));

	for (int i = 0; i < 10; i++)
	{
		spriteNumberNum1[i] = std::unique_ptr<Sprite>(Sprite::Create(71+i, { 260 - 10, 656 - MAPWALLSIZE - 96 }));
			}
	for (int i = 0; i < 10; i++)
	{
		spriteNumberNum10[i] = std::unique_ptr<Sprite>(Sprite::Create(71+i, { 260 - 58, 656 - MAPWALLSIZE - 96 }));
	}

	spriteEnemyStop = std::unique_ptr<Sprite>(Sprite::Create(31, { 990, 850 }));
	 spriteEnemyStop->SetAnchorPoint(XMFLOAT2(0.5f,0.5f));
	 spriteEnemyStop->SetSize(XMFLOAT2(stopFontSize));

	 spriteEnemySpot = std::unique_ptr<Sprite>(Sprite::Create(32, { 990, 850 }));
	 spriteEnemySpot->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	 spriteEnemySpot->SetSize(XMFLOAT2(spotFontSize));

	 spriteSpotEffect = std::unique_ptr<Sprite>(Sprite::Create(33, { 84,650 - 16 - 96 }));
	for (int x = 0; x < MAPVALUE; x++)
	{
		for (int y = 0; y < MAPVALUE; y++)
		{
			spriteMapWall[y][x] = std::unique_ptr<Sprite>(Sprite::Create(2, {-16 + 100 + (MAPWALLSIZE * (MAPVALUE - x)),650 + (MAPWALLSIZE * y )}));
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

	//マップ読み込み
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
	//クリスタル初期化
	for (int i = 0; i < 11; i++)
	{
		crystalGetFlag[i] = false;
	}
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
	//マップの生成
	MapRandam(mapWallLeftUp, mapWallLeftUp1, 0, 0);
	MapRandam(mapWallLeftCenter, mapWallLeftCenter1, 0, 1);
	MapRandam(mapWallLeftDown, mapWallLeftDown1, 0, 2);
	MapRandam(mapWallCenterUp, mapWallCenterUp1, 1, 0);
	MapRandam(mapWallCenterCenter, mapWallCenterCenter1, 1, 1);
	MapRandam(mapWallCenterDown, mapWallCenterDown1, 1, 2);
	MapRandam(mapWallRightUp, mapWallRightUp1, 2, 0);
	MapRandam(mapWallRightCenter, mapWallRightCenter1, 2, 1);
	MapRandam(mapWallRightDown, mapWallRightDown1, 2, 2);
}

void MapChip::MapRandam(int mapArea[7][7], int mapArea2[7][7],int X,int Z)
{
	//マップ選択
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<>rand2(0, 1);//0~2の範囲
	int num = rand2(mt);

	//マップの割り当て
	for (int z = 0; z < MAPVALUE / 3; z++){
		for (int x = 0; x < MAPVALUE / 3; x++){
			if (num == 0)
			{
				mapWall[z + (7 * Z)][x + (7 * X)] = mapArea[z][x];
			}
			else if (num == 1)			
			{
				mapWall[z + (7 * Z)][x + (7 * X)] = mapArea2[z][x];
			}
		}
	}
}

void MapChip::MapMove(XMFLOAT2 mapPos)
{
	//ミニマップの壁移動
	for (int x = 0; x < MAPVALUE; x++){
		for (int y = 0; y < MAPVALUE; y++){
			spriteMapWall[y][x]->SetPosition({ mapPos.x - MAPWALLSIZE + 100 + (MAPWALLSIZE * (MAPVALUE - x)), mapPos.y + 650 + (MAPWALLSIZE * y) });
		}
	}
	//ミニマップのクリスタル移動
	for (int i = 0; i < 11; i++){
		spriteCrystal[i]->SetPosition({ mapPos.x + mapCrystalPos[i].x, mapPos.y + mapCrystalPos[i].y });
	}
}

void MapChip::Update(XMFLOAT3 pos, XMFLOAT2 mapPos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3)
{	
	//ミニマップ移動
	MapMove(mapPos);

	//ステージオブジェクトのアップデート
	StageUpdate(enemyPos1, enemyPos2,enemyPos3);			
	
	//ドアのオープン
	DoorOpen(pos);

	//マップ内でのプレイヤーの位置のアップデート
	PlayerPosConvertMap(pos);

	//クリスタル関連
	CrystalUpdate(pos);

	//敵停止
	TimeStop();

	//スポット
	EnemyDisplay();
}

void MapChip::StageUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3)
{
	//ライトの値送り
	bool lightSilen = LightAction();
	//マップのオブジェクトのアップデート
	for (int x = 0; x < 7; x++)
	{
		for (int z = 0; z < 7; z++)
		{
			//点滅関連
			int lightFlag = lightSilen;
			if (ArrayValue(68.0f + (-24.0f * (6 - x)), -76.0f + (24.0f * z)) == 1) {
				lightFlag = 0;
			}
			for (int j = 0; j < 3; j++)
			{
				//壁のアップデート
				objMapWall[j + 3 * z][0 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);
				objMapWall[j + 3 * z][1 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);
				objMapWall[j + 3 * z][2 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);

				//天井のアップデート	
				objCeiling[j + 3 * z][0 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);
				objCeiling[j + 3 * z][1 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);
				objCeiling[j + 3 * z][2 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);

				//床のアップデート
				objFloor[j + 3 * z][0 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);
				objFloor[j + 3 * z][1 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);
				objFloor[j + 3 * z][2 + 3 * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);
			}
		}
	}
	//ドアのアップデート
	for (int i = 0; i < 4; i++)
	{
		objMapDoor[i]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}
	//クリスタルのアップデート
	for (int i = 0; i < 11; i++)
	{
		objCrystal[i]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}

	//絵画と机のアップデート
	for (int x = 0; x < 21; x += 2)
	{
		for (int y = 0; y < 21; y += 2)
		{
			objPictureFrame1[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 80.0f - (x * WALLSIZE), 4.25f, 76.0f - (y * WALLSIZE) }), lightSilen, 0);
			objDesk1[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ +0.5f + 80.0f - (x * WALLSIZE),2.0f,76.0f - (y * WALLSIZE) }), lightSilen, 0);

			objPictureFrame2[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 72.0f - (x * WALLSIZE),4.25f,76.0f - (y * WALLSIZE) }), lightSilen, 0);
			objDesk2[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ -0.5f + 72.0f - (x * WALLSIZE),2.0f,76.0f - (y * WALLSIZE) }), lightSilen, 0);

			objPictureFrame3[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 76.0f - (x * WALLSIZE),4.25f,72.0f - (y * WALLSIZE) }), lightSilen, 0);
			objDesk3[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 76.0f - (x * WALLSIZE),2.0f,-0.5f + 72.0f - (y * WALLSIZE) }), lightSilen, 0);

			objPictureFrame4[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 76.0f - (x * WALLSIZE),4.25f,80.0f - (y * WALLSIZE) }), lightSilen, 0);
			objDesk4[y][x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3({ 76.0f - (x * WALLSIZE),2.0f,+0.5f + 80.0f - (y * WALLSIZE) }), lightSilen, 0);
		}
	}
}

void MapChip::DoorOpen(XMFLOAT3 pos)
{
	//プレイヤーのマップの座標
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((21 + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((21 + 1) / 2));

	//ドア関連
	if (gateOpenFlag == true && doorAngle[0] > 0){
		doorAngle[1] += 10;
		doorAngle[0] -= 10;
		doorAngle[3] -= 10;
		doorAngle[2] += 10;
		mapWall[12][10] = 0;
		mapWall[8][10] = 0;
	}

	//ドアの角度をセット
	for (int i = 0; i < 4; i++)
	{
		objMapDoor[i]->SetRotation(XMFLOAT3({ 0.0f,doorAngle[i],0.0f }));
	}	

	//ゲートオープン
	if (Input::GetInstance()->KeybordTrigger(DIK_E) && mapX == 10 && mapY == 9)
	{
		gateOpenFlag = true;
	}
}

void MapChip::PlayerPosConvertMap(XMFLOAT3 pos)
{
	//プレイヤーの座標をマップチップに変換
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((21 + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((21 + 1) / 2));
	mapPlayer[mapX][mapY] = 1;
	mapPlayer[mapX + 1][mapY] = 0;
	mapPlayer[mapX - 1][mapY] = 0;
	mapPlayer[mapX][mapY + 1] = 0;
	mapPlayer[mapX][mapY - 1] = 0;
}

void MapChip::CrystalUpdate(XMFLOAT3 pos)
{
	//クリスタル関連
	for (int i = 0; i < 11; i++)
	{
		if (crystalGetFlag[i] == false)
		{
			XMFLOAT3 crystalAngle = objCrystal[i]->GetRotation();
			crystalAngle.y++;
			objCrystal[i]->SetRotation(crystalAngle);
			if (crystalGetFlag[i] = Collision::ChenkSphere2Sphere(pos, crystalPos[i], 3.25f, 1.0f))
			{
				number--;
			}
		}
	}

	//クリスタル入手したか
	if (crystalGetFlag[0] && crystalGetFlag[1] && crystalGetFlag[2] && crystalGetFlag[3] && crystalGetFlag[4] &&
		crystalGetFlag[5] && crystalGetFlag[6] && crystalGetFlag[7] && crystalGetFlag[8] && crystalGetFlag[9] && 
		crystalGetFlag[10]){
		allGetFlag = true;
	}

	//数字のフォント
	if (number >= 10) {
		for (int i = 0; i < 10; i++) {
			spriteNumberNum1[i]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		}
	}
	else {
		for (int i = 0; i < 10; i++) {
			spriteNumberNum1[i]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
		}
	}
}

int MapChip::ArrayValue(float x, float y)
{
	//指定した位置のマップの情報取得
	int mapY = int((y / WALLSIZE) + ((MAPVALUE+1) / 2));
	int mapX = int((x / WALLSIZE) + ((MAPVALUE+1) / 2));
	return mapWall[mapY][mapX];
}

void MapChip::Draw()
{
	//壁
	for (int x = 0; x < MAPVALUE; x++)
	{
		for (int y = 0; y < MAPVALUE; y++)
		{
			if (mapWall[y][x] == 1)
			{
				objMapWall[y][x]->Draw();
			}
		}
	}
	//天井
	for (int x = 0; x < MAPVALUE; x++)
	{
		for (int y = 0; y < MAPVALUE; y++)
		{
			if (mapWall[y][x] != 1)
			{
				objCeiling[y][x]->Draw();
			}
		}
	}
	//床
	for (int x = 0; x < MAPVALUE; x++)
	{
		for (int y = 0; y < MAPVALUE; y++)
		{
			if (mapWall[y][x] != 1)
			{
				objFloor[y][x]->Draw();
			}
		}
	}
	//クリスタル
	for (int i = 0; i < 11; i++)
	{
		if(crystalGetFlag[i] == false)
		{
			objCrystal[i]->Draw();
		}
	}
	//ドア
	for (int i = 0; i < 4; i++)
	{
		objMapDoor[i]->Draw();
	}
	//絵画
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
	//マップ内の座標系の取得
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((21 + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((21 + 1) / 2));
	
	//ミニマップの裏
	spriteMapBack->Draw(1.0f);//スポットしてない時
	if (displayFlag) {
		spriteSpotEffect->Draw(1.0f);//スポット中
	}
	//壁
	for (int x = 0; x < MAPVALUE; x++){
		for (int y = 0; y < MAPVALUE; y++){
			if (mapWall[y][x] == 1 && spriteMapWall[y][x]->GetPosition().x < 420 && spriteMapWall[y][x]->GetPosition().x > 100
				&& spriteMapWall[y][x]->GetPosition().y > 650 && spriteMapWall[y][x]->GetPosition().y < 986)
			{
				spriteMapWall[y][x]->Draw(1.0f);
			}
		}
	}

	//クリスタル
	for (int i = 0; i < 11; i++)
	{
		if (crystalGetFlag[i] == false && spriteCrystal[i]->GetPosition().x < 420 && spriteCrystal[i]->GetPosition().x > 100
			&& spriteCrystal[i]->GetPosition().y > 650 && spriteCrystal[i]->GetPosition().y < 986)
		{
			spriteCrystal[i]->Draw(1.0f);
		}
	}
	//ミニマップのフレーム
	if (!displayFlag) {
		spriteMapFrame->Draw(1.0f);
	}
	
	//数字
	for (int i = 0; i < 9; i++)
	{
		if (number == i + 1)
		{
			spriteNumberNum1[number - 1]->Draw(1.0f);
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

	//スポットフォント
	if (spotSprieteTime < 80 && displayFlag)
	{	
		spotSprieteTime++;
		spriteEnemySpot->Draw(spotAlpha);
	}
	
	//ストップフォント
	if (stopSprieteTime < 80 && stopFlag)
	{
		stopSprieteTime++;
		spriteEnemyStop->Draw(stopAlpha);
	}
	
	//ゲート開くフラグ
	if (gateOpenFlag == false && mapX == 10 && mapY == 9)
	{
		spriteDoorOpen->Draw(1.0f);
	}
}

void MapChip::TimeStop()
{
	//敵停止
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
	
	//ストップフォント関連
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
}

void MapChip::EnemyDisplay()
{
	//敵スポット
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

	//スポットフォント関連
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
}

bool MapChip::LightAction()
{
	//ライトの点滅
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
