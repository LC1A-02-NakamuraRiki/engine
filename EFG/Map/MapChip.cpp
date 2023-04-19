#include "MapChip.h"
#include "Collision.h"
#include<time.h>
#include<random>
#include "Input.h"
#include <cassert>
#include <sstream>
#include <iomanip>

MapChip::~MapChip()
{
}

void MapChip::Initialize()
{
	InitMapObject();
	
	InitSprite();
}

void MapChip::InitializeValue()
{
	//クリスタル初期化
	for (int i = 0; i < CRYSTALVALUE; i++){
		crystalGetFlag[i] = false;
	}
	allGetFlag = false;
	MapCreate();
	number = CRYSTALVALUE;
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

	number = CRYSTALVALUE;
	gateOpenFlag = false;

	lightAction = 0;
	lightCount = 0; 
}

void MapChip::MapCreate()
{
	//マップの生成
	MapRandam(mapWallLeftUp1, mapWallLeftUp1, 0, 0);
	MapRandam(mapWallLeftCenter1, mapWallLeftCenter1, 0, 1);
	MapRandam(mapWallLeftDown1, mapWallLeftDown1, 0, 2);
	MapRandam(mapWallCenterUp1, mapWallCenterUp1, 1, 0);
	MapRandam(mapWallCenterCenter1, mapWallCenterCenter1, 1, 1);
	MapRandam(mapWallCenterDown1, mapWallCenterDown1, 1, 2);
	MapRandam(mapWallRightUp1, mapWallRightUp1, 2, 0);
	MapRandam(mapWallRightCenter1, mapWallRightCenter1, 2, 1);
	MapRandam(mapWallRightDown1, mapWallRightDown1, 2, 2);
}

void MapChip::MapRandam(int mapArea[AREAVALUE][AREAVALUE], int mapArea2[AREAVALUE][AREAVALUE],int X,int Z)
{
	//マップ選択
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<>rand2(0, 1);//0~2の範囲
	int num = rand2(mt);

	//マップの割り当て
	const int MAXAREA = 3;
	for (int z = 0; z < MAPVALUE / MAXAREA; z++){
		for (int x = 0; x < MAPVALUE / MAXAREA; x++){
			if (num == 0){
				mapWall[z + (MAPAREAVALUE * Z)][x + (MAPAREAVALUE * X)] = mapArea2[z][x];
			}
			else if (num == 1){
				mapWall[z + (MAPAREAVALUE * Z)][x + (MAPAREAVALUE * X)] = mapArea2[z][x];
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
	for (int i = 0; i < CRYSTALVALUE; i++){
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
	for (int x = 0; x < MAPAREAVALUE; x++){
		for (int z = 0; z < MAPAREAVALUE; z++){
			//点滅関連
			int lightFlag = lightSilen;
			if (ArrayValue(68.0f + (-24.0f * (6 - x)), -76.0f + (24.0f * z)) == 1) {
				lightFlag = 0;
			}
		}
	}
	//ドアのアップデート
	for (int i = 0; i < DOORVALUE; i++){
		objMapDoor[i]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}
	//クリスタルのアップデート
	for (int i = 0; i < CRYSTALVALUE; i++){
		objCrystal[i]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}

	//絵画と机のアップデート
	for (int x = 0; x < MAPVALUE; x += 2){
		for (int y = 0; y < MAPVALUE; y += 2){
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
	for (auto& object : objects) {
		object->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}
	for (auto& object : randamObjects) {
		object->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}
}


void MapChip::DoorOpen(XMFLOAT3 pos)
{
	//プレイヤーのマップの座標
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((MAPVALUE + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((MAPVALUE + 1) / 2));

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
	for (int i = 0; i < DOORVALUE; i++){
		objMapDoor[i]->SetRotation(XMFLOAT3({ 0.0f,doorAngle[i],0.0f }));
	}	

	//ゲートオープン
	if (Input::GetInstance()->KeybordTrigger(DIK_E) && mapX == 10 && mapY == 9){
		gateOpenFlag = true;
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
	if (crystalGetFlag[0] && crystalGetFlag[1] && crystalGetFlag[2] && crystalGetFlag[3] && crystalGetFlag[4] &&
		crystalGetFlag[5] && crystalGetFlag[6] && crystalGetFlag[7] && crystalGetFlag[8] && crystalGetFlag[9] && 
		crystalGetFlag[10]){
		allGetFlag = true;
	}

	//数字のフォント
	if (number >= MAXNUMBER) {
		for (int i = 0; i < MAXNUMBER; i++) {
			spriteNumberNum1[i]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		}
	}
	else {
		for (int i = 0; i < MAXNUMBER; i++) {
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
	for (auto& object : objects) {
		object->Draw();
	}
	for (auto& object : randamObjects) {
		object->Draw();
	}
}

void MapChip::DrawSprite(XMFLOAT3 pos)
{
	//マップ内の座標系の取得
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((MAPVALUE + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((MAPVALUE + 1) / 2));
	
	//ミニマップの裏
	spriteMapBack->Draw(1.0f);//スポットしてない時
	if (displayFlag) {
		spriteSpotEffect->Draw(1.0f);//スポット中
	}
	//壁
	for (int x = 0; x < MAPVALUE; x++){
		for (int y = 0; y < MAPVALUE; y++){
			if (mapWall[y][x] == 1 && spriteMapWall[y][x]->GetPosition().x < 420 && spriteMapWall[y][x]->GetPosition().x > 100
				&& spriteMapWall[y][x]->GetPosition().y > 650 && spriteMapWall[y][x]->GetPosition().y < 986){
				spriteMapWall[y][x]->Draw(1.0f);
			}
		}
	}

	//クリスタル
	for (int i = 0; i < CRYSTALVALUE; i++){
		if (crystalGetFlag[i] == false && spriteCrystal[i]->GetPosition().x < 420 && spriteCrystal[i]->GetPosition().x > 100
			&& spriteCrystal[i]->GetPosition().y > 650 && spriteCrystal[i]->GetPosition().y < 986){
			spriteCrystal[i]->Draw(1.0f);
		}
	}
	//ミニマップのフレーム
	if (!displayFlag) {
		spriteMapFrame->Draw(1.0f);
	}
	
	//数字
	const int MAXNUMUBER = 9;
	const int MAXNUMUBERTENNUM = 10;
	const int MAXNUMUBERNUM = 11;
	for (int i = 0; i < MAXNUMUBER; i++){
		if (number == i + 1){
			spriteNumberNum1[number - 1]->Draw(1.0f);
		}
	}
	if (number == MAXNUMUBERTENNUM){
		spriteNumberNum10[0]->Draw(1.0f);
		spriteNumberNum1[9]->Draw(1.0f);
	}
	if (number == MAXNUMUBERNUM){
		spriteNumberNum1[0]->Draw(1.0f);
		spriteNumberNum10[0]->Draw(1.0f);
	}

	//スポットフォント
	if (spotSprieteTime < 80 && displayFlag){	
		spotSprieteTime++;
		spriteEnemySpot->Draw(spotAlpha);
	}
	
	//ストップフォント
	if (stopSprieteTime < 80 && stopFlag){
		stopSprieteTime++;
		spriteEnemyStop->Draw(stopAlpha);
	}
	
	//ゲート開くフラグ
	if (gateOpenFlag == false && mapX == 10 && mapY == 9){
		spriteDoorOpen->Draw(1.0f);
	}
}

void MapChip::TimeStop()
{
	//敵停止
	const int MAXSTOPTAIME = 300;
	if (crystalGetFlag[5] && stopTime == 0){
		stopFlag = true;
	}
	if (stopFlag){
		stopTime++;
	}
	if (stopTime > MAXSTOPTAIME){
		stopFlag = false;
	}
	
	//ストップフォント関連
	if (stopSprieteTime > 60 && stopSprieteTime < 80 && stopFlag){
		stopAlpha -= 0.05f;
	}
	if (stopSprieteTime < 60 && stopFontSize.x > 1200 && stopFlag){
		stopFontSize.x -= 1200;
		stopFontSize.y -= 200;
		spriteEnemyStop->SetSize(stopFontSize);
	}
}

void MapChip::EnemyDisplay()
{
	//敵スポット
	if (crystalGetFlag[3] && displayTime == 0){
		displayFlag = true;
	}
	if (displayFlag){
		displayTime++;
	}
	if (displayTime > 600){
		displayFlag = false;
	}

	//スポットフォント関連
	if (spotSprieteTime > 60 && spotSprieteTime < 80 && displayFlag){
		spotAlpha -= 0.05f;
	}
	if (spotSprieteTime < 60 && spotFontSize.x > 1200 && displayFlag){
		spotFontSize.x -= 1200;
		spotFontSize.y -= 200;
		spriteEnemySpot->SetSize(spotFontSize);
	}
}

void MapChip::InitMapObject()
{
	//モデル読み込み
	modelPictureFrame = std::unique_ptr<Model>(Model::CreateFromObject("pictureFrame", false));
	modelDesk = std::unique_ptr<Model>(Model::CreateFromObject("desk", false));
	modelMapWall = std::unique_ptr<Model>(Model::CreateFromObject("wall", false));
	for (int x = 0; x < MAPVALUE; x++) {
		for (int y = 0; y < MAPVALUE; y++) {
			objPictureFrame1[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelPictureFrame.get()));
			objPictureFrame1[y][x]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
			objPictureFrame1[y][x]->SetPosition(XMFLOAT3({ 80.0f - (x * WALLSIZE),4.25f,76.0f - (y * WALLSIZE) }));

			objDesk1[y][x] = std::unique_ptr<Object3d>(Object3d::Create(modelDesk.get()));
			objDesk1[y][x]->SetScale(XMFLOAT3({ 0.02f, 0.065f, 0.05f }
				
			));
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
		}
	}
	modelCeiling = std::unique_ptr<Model>(Model::CreateFromObject("ceiling", false));
	modelFlat = std::unique_ptr<Model>(Model::CreateFromObject("roof", false));
	modelFloor = std::unique_ptr<Model>(Model::CreateFromObject("floor", false));
	modelCrystal = std::unique_ptr<Model>(Model::CreateFromObject("crystal", false));
	modelItemCrystal = std::unique_ptr<Model>(Model::CreateFromObject("itemCrystal", false));
	modelItemCrystal2 = std::unique_ptr<Model>(Model::CreateFromObject("itemCrystal2", false));
	for (int i = 0; i < CRYSTALVALUE; i++) {
		objCrystal[i] = std::unique_ptr<Object3d>(Object3d::Create(modelCrystal.get()));
		objCrystal[i]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
		crystalGetFlag[i] = false;
	}
	objCrystal[3] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal.get()));
	objCrystal[5] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal2.get()));
	objCrystal[3]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
	objCrystal[5]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
	for (int i = 0; i < CRYSTALVALUE; i++) {
		objCrystal[i]->SetPosition(crystalPos[i]);
	}
	for (int i = 0; i < DOORVALUE; i++)
	{
		modelDoor[i] = std::unique_ptr<Model>(Model::CreateFromObject("door", false));
		objMapDoor[i] = std::unique_ptr<Object3d>(Object3d::Create(modelDoor[i].get()));
		objMapDoor[i]->SetRotation(XMFLOAT3({ 0.0f,doorAngle[i],0.0f }));
		objMapDoor[i]->SetScale(XMFLOAT3({ 1.0f,1.5f,2.0f }));
	}
	objMapDoor[0]->SetPosition(XMFLOAT3({ -0.2f,0.2f,-16.0f }));
	objMapDoor[1]->SetPosition(XMFLOAT3({ -7.8f,0.2f,-16.0f }));
	objMapDoor[2]->SetPosition(XMFLOAT3({ -0.2f,0.2f,8.0f }));
	objMapDoor[3]->SetPosition(XMFLOAT3({ -7.8f,0.2f,8.0f }));

	//// レベルデータの読み込み
	editData = EditLoader::LoadFile("centerMap1");
	randamEditData = EditLoader::LoadFile("centerMap3");

	models.insert(std::make_pair("wall", modelMapWall.get()));
	models.insert(std::make_pair("floor", modelFloor.get()));
	models.insert(std::make_pair("roof", modelFlat.get()));
	models.insert(std::make_pair("ceiling", modelCeiling.get()));

	// レベルデータからオブジェクトを生成、配置
	for (auto& objectData : editData->objects) {
		// ファイル名から登録済みモデルを検索
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) {
			model = it->second;
		}
		// モデルを指定して3Dオブジェクトを生成
		Object3d* newObject = Object3d::Create(model);
		// 座標
		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, objectData.translation);
		newObject->SetPosition(pos);
		// 回転角
		DirectX::XMFLOAT3 rot;
		DirectX::XMStoreFloat3(&rot, objectData.rotation);
		newObject->SetRotation(rot);
		// 大きさ
		DirectX::XMFLOAT3 scale;
		DirectX::XMStoreFloat3(&scale, objectData.scaling);
		newObject->SetScale(scale);
		// 配列に登録
		objects.push_back(newObject);
	}
	for (auto& objectData : randamEditData->objects) {
		// ファイル名から登録済みモデルを検索
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) {
			model = it->second;
		}
		// モデルを指定して3Dオブジェクトを生成
		Object3d* newObject = Object3d::Create(model);
		// 座標
		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, objectData.translation);
		newObject->SetPosition(pos);
		// 回転角
		DirectX::XMFLOAT3 rot;
		DirectX::XMStoreFloat3(&rot, objectData.rotation);
		newObject->SetRotation(rot);
		// 大きさ
		DirectX::XMFLOAT3 scale;
		DirectX::XMStoreFloat3(&scale, objectData.scaling);
		newObject->SetScale(scale);
		// 配列に登録
		objects.push_back(newObject);
	}
}

void MapChip::InitSprite()
{
	//画像の読み込み
	Sprite::LoadTexture(2, L"Resources/mapWall.png");
	Sprite::LoadTexture(5, L"Resources/miniMapBack.png");
	Sprite::LoadTexture(7, L"Resources/crystal.png");
	Sprite::LoadTexture(71, L"Resources/number/1.png");
	Sprite::LoadTexture(72, L"Resources/number/2.png");
	Sprite::LoadTexture(73, L"Resources/number/3.png");
	Sprite::LoadTexture(74, L"Resources/number/4.png");
	Sprite::LoadTexture(75, L"Resources/number/5.png");
	Sprite::LoadTexture(76, L"Resources/number/6.png");
	Sprite::LoadTexture(77, L"Resources/number/7.png");
	Sprite::LoadTexture(78, L"Resources/number/8.png");
	Sprite::LoadTexture(79, L"Resources/number/9.png");
	Sprite::LoadTexture(80, L"Resources/number/0.png");
	Sprite::LoadTexture(17, L"Resources/crystal2.png");
	Sprite::LoadTexture(130, L"Resources/crystal3.png");
	Sprite::LoadTexture(26, L"Resources/miniMapFrame.png");
	Sprite::LoadTexture(31, L"Resources/EnemyStop.png");
	Sprite::LoadTexture(32, L"Resources/EnemySpotted.png");
	Sprite::LoadTexture(33, L"Resources/MiniMapBack2.png");
	Sprite::LoadTexture(45, L"Resources/Open.png");

	//スプライトの初期化
	for (int x = 0; x < MAPVALUE; x++) {
		for (int y = 0; y < MAPVALUE; y++) {
			spriteMapWall[y][x] = nullptr;
		}
	}

	for (int i = 0; i < MAXNUMBER; i++) {
		spriteNumberNum1[i] = std::unique_ptr<Sprite>(Sprite::Create(71 + i, { 260 - 10, 656 - MAPWALLSIZE - 96 }));
		spriteNumberNum10[i] = std::unique_ptr<Sprite>(Sprite::Create(71 + i, { 260 - 58, 656 - MAPWALLSIZE - 96 }));
	}

	spriteEnemyStop = std::unique_ptr<Sprite>(Sprite::Create(31, { 990, 850 }));
	spriteEnemyStop->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	spriteEnemyStop->SetSize(XMFLOAT2(stopFontSize));

	spriteEnemySpot = std::unique_ptr<Sprite>(Sprite::Create(32, { 990, 850 }));
	spriteEnemySpot->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	spriteEnemySpot->SetSize(XMFLOAT2(spotFontSize));

	for (int x = 0; x < MAPVALUE; x++) {
		for (int y = 0; y < MAPVALUE; y++) {
			spriteMapWall[y][x] = std::unique_ptr<Sprite>(Sprite::Create(2, { -16 + 100 + (MAPWALLSIZE * (MAPVALUE - x)),650 + (MAPWALLSIZE * y) }));
		}
	}

	for (int i = 0; i < CRYSTALVALUE; i++) {
		spriteCrystal[i] = std::unique_ptr<Sprite>(Sprite::Create(7, mapCrystalPos[i]));
	}
	spriteCrystal[3] = std::unique_ptr<Sprite>(Sprite::Create(17, mapCrystalPos[3]));
	spriteCrystal[5] = std::unique_ptr<Sprite>(Sprite::Create(130, mapCrystalPos[5]));
	spriteSpotEffect = std::unique_ptr<Sprite>(Sprite::Create(33, { 84,650 - 16 - 96 }));
	spriteDoorOpen = std::unique_ptr<Sprite>(Sprite::Create(45, { 990, 850 }));
	spriteDoorOpen->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	spriteMapBack = std::unique_ptr<Sprite>(Sprite::Create(5, { -16 + 100,650 - 16 - 96 }));
	spriteMapFrame = std::unique_ptr<Sprite>(Sprite::Create(26, { -16 + 100,650 - 16 - 96 }));
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
