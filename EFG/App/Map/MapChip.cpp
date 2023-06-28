#include "MapChip.h"
#include "Collision.h"
#include<time.h>
#include<random>
#include "Input.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "MapEffect.h"
#include "MapUI.h"

MapChip::~MapChip()
{
}

void MapChip::Initialize()
{
	//マップ初期化
	InitMapObject();
	
	//スプライト初期化
	mapUI = std::make_unique<MapUI>();
	mapUI->InitSprite();
} 

void MapChip::InitMapObject()
{
	//ロードマップ
	LoadMap();

	//モデル読み込み
	LoadModel();

	//クリスタル初期化
	InitCrystal();

	//ドア初期化
	InitDoor();
}

void MapChip::LoadMap()
{
	//マップ読み込み1種類目
	LoadCSV(mapWallLeftUp, "Resources/map/a1.csv");													//左上
	LoadCSV(mapWallLeftCenter, "Resources/map/a2.csv");												//左中心
	LoadCSV(mapWallLeftDown, "Resources/map/a3.csv");												//左下
	LoadCSV(mapWallCenterUp, "Resources/map/a4.csv");												//中心上
	LoadCSV(mapWallCenterCenter, "Resources/map/a5.csv");											//中心中心
	LoadCSV(mapWallCenterDown, "Resources/map/a6.csv");												//中心下
	LoadCSV(mapWallRightUp, "Resources/map/a7.csv");												//右上
	LoadCSV(mapWallRightCenter, "Resources/map/a8.csv");											//右中心
	LoadCSV(mapWallRightDown, "Resources/map/a9.csv");												//右下

	//マップ読み込み2種類目
	LoadCSV(mapWallLeftUp1, "Resources/map/b1.csv");												//左上	
	LoadCSV(mapWallLeftCenter1, "Resources/map/b2.csv");											//左中心
	LoadCSV(mapWallLeftDown1, "Resources/map/b3.csv");												//左下
	LoadCSV(mapWallCenterUp1, "Resources/map/b4.csv");												//中心上
	LoadCSV(mapWallCenterCenter1, "Resources/map/b5.csv");											//中心中心
	LoadCSV(mapWallCenterDown1, "Resources/map/b6.csv");											//中心下
	LoadCSV(mapWallRightUp1, "Resources/map/b7.csv");												//右上
	LoadCSV(mapWallRightCenter1, "Resources/map/b8.csv");											//右中心
	LoadCSV(mapWallRightDown1, "Resources/map/b9.csv");												//右下
}

void MapChip::LoadModel()
{
	//モデル読み込み
	modelPictureFrame = std::unique_ptr<Model>(Model::CreateFromObject("pictureFrame", false));		//額縁
	modelDesk = std::unique_ptr<Model>(Model::CreateFromObject("desk", false));						//机
	modelMapWall = std::unique_ptr<Model>(Model::CreateFromObject("wall", false));					//壁
	modelFloor = std::unique_ptr<Model>(Model::CreateFromObject("floor", false));					//床
	modelCrystal = std::unique_ptr<Model>(Model::CreateFromObject("crystal", false));				//クリスタル
	modelItemCrystal = std::unique_ptr<Model>(Model::CreateFromObject("itemCrystal", false));		//クリスタル
	modelItemCrystal2 = std::unique_ptr<Model>(Model::CreateFromObject("itemCrystal2", false));		//クリスタル
	modelCeiling = std::unique_ptr<Model>(Model::CreateFromObject("ceiling", false));				//ライト有天井
	modelFlat = std::unique_ptr<Model>(Model::CreateFromObject("roof", false));						//ライト無天井
}

void MapChip::InitCrystal()
{
	//クリスタル初期化
	for (int i = 0; i < CRYSTALVALUE; i++) {
		objCrystal[i] = std::unique_ptr<Object3d>(Object3d::Create(modelCrystal.get()));
		if(i == SPOTCRYSTALNUM){ objCrystal[SPOTCRYSTALNUM] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal.get())); }
		if (i == STOPCRYSTALNUM) { objCrystal[STOPCRYSTALNUM] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal2.get())); }
		objCrystal[i]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
		crystalGetFlag[i] = false;
		objCrystal[i]->SetPosition(crystalPos[i]);
	}
}

void MapChip::InitDoor()
{
	//ドア初期化
	for (int i = 0; i < DOORVALUE; i++){
		modelDoor[i] = std::unique_ptr<Model>(Model::CreateFromObject("door", false));
		objMapDoor[i] = std::unique_ptr<Object3d>(Object3d::Create(modelDoor[i].get()));
		objMapDoor[i]->SetRotation(XMFLOAT3({ 0.0f,doorAngle[i],0.0f }));
		objMapDoor[i]->SetScale(XMFLOAT3({ 1.0f,1.5f,2.0f }));
		//ドアの位置セット
		objMapDoor[i]->SetPosition(mapDoorPos[i]);
	}
}

void MapChip::InitializeValue()
{
	MapCreate();													//マップ生成
}

void MapChip::MapCreate()
{
	//マップの生成
	MapRandam(mapWallLeftUp, mapWallLeftUp1, UpOrLeft, UpOrLeft);											//左上
	MapRandam(mapWallLeftCenter, mapWallLeftCenter1, UpOrLeft, Center);										//左中心
	MapRandam(mapWallLeftDown, mapWallLeftDown1, UpOrLeft, DownOrRight);									//左下
	MapRandam(mapWallCenterUp, mapWallCenterUp1, Center, UpOrLeft);											//中心上
	MapRandam(mapWallCenterCenter, mapWallCenterCenter1, Center, Center);									//中心中心
	MapRandam(mapWallCenterDown, mapWallCenterDown1, Center, DownOrRight);									//中心下
	MapRandam(mapWallRightUp, mapWallRightUp1, 2, UpOrLeft);												//右上
	MapRandam(mapWallRightCenter, mapWallRightCenter1, DownOrRight, Center);								//右中心
	MapRandam(mapWallRightDown, mapWallRightDown1, DownOrRight, DownOrRight);								//右下
}

void MapChip::MapRandam(int mapArea[AREAVALUE][AREAVALUE], int mapArea2[AREAVALUE][AREAVALUE],int X,int Z)
{
	//マップ選択
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<>rand2(0, 1);//0~2の範囲
	int num = rand2(mt);

	//マップの割り当て
	for (int z = 0; z < MAPVALUE / MAXAREA; z++){
		for (int x = 0; x < MAPVALUE / MAXAREA; x++){
			if (num == 0){mapWall[z + (MAPAREAVALUE * Z)][x + (MAPAREAVALUE * X)] = mapArea2[z][x];}//マップの種類１
			else if (num == 1){mapWall[z + (MAPAREAVALUE * Z)][x + (MAPAREAVALUE * X)] = mapArea[z][x];}//マップの種類２
		}
	}
}

void MapChip::Update(XMFLOAT3 pos, XMFLOAT2 mapPos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3)
{	
	//ミニマップ移動
	mapUI->MapUIUpdate(mapPos,number);

	//ステージオブジェクトのアップデート
	StageUpdate(pos,enemyPos1, enemyPos2,enemyPos3);			

	//マップ内でのプレイヤーの位置のアップデート
	PlayerPosConvertMap(pos);

	//クリスタル関連
	CrystalUpdate(pos);

	//敵停止
	mapUI->TimeStop();

	//スポット
	mapUI->EnemyDisplay();
}

void MapChip::StageUpdate(XMFLOAT3 pos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3)
{
	//ライトの値送り
	lightSilen = MapEffect::LightAction(lightAction, lightCount);

	//ドアのアップデート
	for (int i = 0; i < DOORVALUE; i++){
		objMapDoor[i]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}

	//クリスタルのアップデート
	for (int i = 0; i < CRYSTALVALUE; i++){
		objCrystal[i]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}

	//マップのオブジェクトのアップデート
	MapUpdate(enemyPos1, enemyPos2, enemyPos3);
}

void MapChip::MapUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3)
{
	for (int x = 0; x < MAPAREAVALUE; x++){
		for (int z = 0; z < MAPAREAVALUE; z++){
			//点滅関連
			int lightFlag = lightSilen;
			if (ArrayValue(68.0f + (-24.0f * (6 - x)), -76.0f + (24.0f * z)) == 1) {
				lightFlag = 0;
			}
			
			//オブジェクトのアップデート
			MapObjUpdate(enemyPos1, enemyPos2, enemyPos3, x, z, lightFlag);
			
			//机と額縁のアップデート
			DeskAndFrameUpdate(enemyPos1, enemyPos2, enemyPos3, lightFlag);
		}
	}
}

void MapChip::MapObjUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3, int x, int z, int lightFlag)
{
	for (int j = 0; j < MAXAREA; j++) {
		for (int k = 0; k < MAXAREA; k++) {
			//壁のアップデート
			objMapWall[j + MAXAREA * z][k + MAXAREA * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);

			//天井のアップデート	
			objCeiling[j + MAXAREA * z][k + MAXAREA * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);

			//床のアップデート
			objFloor[j + MAXAREA * z][k + MAXAREA * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);
		}
	}
}

void MapChip::DeskAndFrameUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3,int lightFlag)
{
	//絵画と机のアップデート
	for (int x = 0; x < MAPVALUE; x += 2) {
		for (int y = 0; y < MAPVALUE; y += 2) {
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

void MapChip::PlayerPosConvertMap(XMFLOAT3 pos)
{
	//プレイヤーの座標をマップチップに変換
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((MAPVALUE + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((MAPVALUE + 1) / 2));
	mapPlayer[mapX][mapY] = 1;
	mapPlayer[mapX + 1][mapY] = 0;
	mapPlayer[mapX - 1][mapY] = 0;
	mapPlayer[mapX][mapY + 1] = 0;
	mapPlayer[mapX][mapY - 1] = 0;
}

void MapChip::CrystalUpdate(XMFLOAT3 pos)
{
	//クリスタル関連
	for (int i = 0; i < CRYSTALVALUE; i++){
		if (crystalGetFlag[i] == false){
			XMFLOAT3 crystalAngle = objCrystal[i]->GetRotation();
			crystalAngle.y++;
			objCrystal[i]->SetRotation(crystalAngle);
			if (crystalGetFlag[i] = Collision::ChenkSphere2Sphere(pos, crystalPos[i], 3.25f, 1.0f)){
				number--;
			}
		}
	}
	
	//クリスタル入手したか
	if (number == 0){
		allGetFlag = true;
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
	//クリスタル
	for (int i = 0; i < CRYSTALVALUE; i++){
		if(crystalGetFlag[i] == false){
			objCrystal[i]->Draw();
		}
	}

	//ドア
	for (int i = 0; i < DOORVALUE; i++){
		objMapDoor[i]->Draw();
	}

	//絵画
	for (int x = 0; x < MAPVALUE; x+=2){
		for (int y = 0; y < MAPVALUE; y+=2){
			if (mapWall[y][x] == 1){
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

void MapChip::MiniMapDraw()
{
	mapUI->DrawSprite(pos, mapWall, crystalGetFlag, number, stopFlag, spotAlphaFlag, stopAlphaFlag, gateOpen);
}