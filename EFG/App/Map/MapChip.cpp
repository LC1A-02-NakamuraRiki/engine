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
	//�}�b�v������
	InitMapObject();
	
	//�X�v���C�g������
	InitSprite();
} 

void MapChip::InitMapObject()
{
	//���[�h�}�b�v
	LoadMap();

	//���f���ǂݍ���
	LoadModel();

	//�N���X�^��������
	InitCrystal();

	//�h�A������
	InitDoor();
}

void MapChip::LoadMap()
{
	//�}�b�v�ǂݍ���1��ޖ�
	LoadCSV(mapWallLeftUp, "Resources/map/a1.csv");													//����
	LoadCSV(mapWallLeftCenter, "Resources/map/a2.csv");												//�����S
	LoadCSV(mapWallLeftDown, "Resources/map/a3.csv");												//����
	LoadCSV(mapWallCenterUp, "Resources/map/a4.csv");												//���S��
	LoadCSV(mapWallCenterCenter, "Resources/map/a5.csv");											//���S���S
	LoadCSV(mapWallCenterDown, "Resources/map/a6.csv");												//���S��
	LoadCSV(mapWallRightUp, "Resources/map/a7.csv");												//�E��
	LoadCSV(mapWallRightCenter, "Resources/map/a8.csv");											//�E���S
	LoadCSV(mapWallRightDown, "Resources/map/a9.csv");												//�E��

	//�}�b�v�ǂݍ���2��ޖ�
	LoadCSV(mapWallLeftUp1, "Resources/map/b1.csv");												//����	
	LoadCSV(mapWallLeftCenter1, "Resources/map/b2.csv");											//�����S
	LoadCSV(mapWallLeftDown1, "Resources/map/b3.csv");												//����
	LoadCSV(mapWallCenterUp1, "Resources/map/b4.csv");												//���S��
	LoadCSV(mapWallCenterCenter1, "Resources/map/b5.csv");											//���S���S
	LoadCSV(mapWallCenterDown1, "Resources/map/b6.csv");											//���S��
	LoadCSV(mapWallRightUp1, "Resources/map/b7.csv");												//�E��
	LoadCSV(mapWallRightCenter1, "Resources/map/b8.csv");											//�E���S
	LoadCSV(mapWallRightDown1, "Resources/map/b9.csv");												//�E��
}

void MapChip::LoadModel()
{
	//���f���ǂݍ���
	modelPictureFrame = std::unique_ptr<Model>(Model::CreateFromObject("pictureFrame", false));		//�z��
	modelDesk = std::unique_ptr<Model>(Model::CreateFromObject("desk", false));						//��
	modelMapWall = std::unique_ptr<Model>(Model::CreateFromObject("wall", false));					//��
	modelFloor = std::unique_ptr<Model>(Model::CreateFromObject("floor", false));					//��
	modelCrystal = std::unique_ptr<Model>(Model::CreateFromObject("crystal", false));				//�N���X�^��
	modelItemCrystal = std::unique_ptr<Model>(Model::CreateFromObject("itemCrystal", false));		//�N���X�^��
	modelItemCrystal2 = std::unique_ptr<Model>(Model::CreateFromObject("itemCrystal2", false));		//�N���X�^��
	modelCeiling = std::unique_ptr<Model>(Model::CreateFromObject("ceiling", false));				//���C�g�L�V��
	modelFlat = std::unique_ptr<Model>(Model::CreateFromObject("roof", false));						//���C�g���V��
}

void MapChip::InitCrystal()
{
	//�N���X�^��������
	for (int i = 0; i < CRYSTALVALUE; i++) {
		objCrystal[i] = std::unique_ptr<Object3d>(Object3d::Create(modelCrystal.get()));
		if(i == 3){ objCrystal[3] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal.get())); }
		if (i == 5) { objCrystal[5] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal2.get())); }
		objCrystal[i]->SetScale(XMFLOAT3({ 0.5f, 0.5f, 0.5f }));
		crystalGetFlag[i] = false;
		objCrystal[i]->SetPosition(crystalPos[i]);
	}
}

void MapChip::InitDoor()
{
	//�h�A������
	for (int i = 0; i < DOORVALUE; i++){
		modelDoor[i] = std::unique_ptr<Model>(Model::CreateFromObject("door", false));
		objMapDoor[i] = std::unique_ptr<Object3d>(Object3d::Create(modelDoor[i].get()));
		objMapDoor[i]->SetRotation(XMFLOAT3({ 0.0f,doorAngle[i],0.0f }));
		objMapDoor[i]->SetScale(XMFLOAT3({ 1.0f,1.5f,2.0f }));
		//�h�A�̈ʒu�Z�b�g
		objMapDoor[i]->SetPosition(mapDoorPos[i]);
	}
}

void MapChip::InitSprite()
{
	//�ǂ̏�����
	for (int x = 0; x < MAPVALUE; x++) {
		for (int y = 0; y < MAPVALUE; y++) {
			spriteMapWall[y][x] = nullptr;
		}
	}

	//����������
	for (int i = 0; i < MAXNUMBER; i++) {
		spriteNumberNum1[i] = std::unique_ptr<Sprite>(Sprite::Create(71 + i, { 260 - 10, 656 - MAPWALLSIZE - 96 }));
		spriteNumberNum10[i] = std::unique_ptr<Sprite>(Sprite::Create(71 + i, { 260 - 58, 656 - MAPWALLSIZE - 96 }));
	}

	//�X�g�b�vUI������
	spriteEnemyStop = std::unique_ptr<Sprite>(Sprite::Create(31, { 990, 850 }));
	spriteEnemyStop->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	spriteEnemyStop->SetSize(XMFLOAT2(stopFontSize));

	//�X�|�b�gUI������
	spriteEnemySpot = std::unique_ptr<Sprite>(Sprite::Create(32, { 990, 850 }));
	spriteEnemySpot->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	spriteEnemySpot->SetSize(XMFLOAT2(spotFontSize));

	//�~�j�}�b�v�̕Ǐ�����
	for (int x = 0; x < MAPVALUE; x++) {
		for (int y = 0; y < MAPVALUE; y++) {
			spriteMapWall[y][x] = std::unique_ptr<Sprite>(Sprite::Create(2, { -16 + 100 + (MAPWALLSIZE * (MAPVALUE - x)),650 + (MAPWALLSIZE * y) }));
		}
	}

	//�N���X�^��������
	for (int i = 0; i < CRYSTALVALUE; i++) { spriteCrystal[i] = std::unique_ptr<Sprite>(Sprite::Create(7, mapCrystalPos[i])); }
	spriteCrystal[3] = std::unique_ptr<Sprite>(Sprite::Create(17, mapCrystalPos[3]));
	spriteCrystal[5] = std::unique_ptr<Sprite>(Sprite::Create(130, mapCrystalPos[5]));
	spriteSpotEffect = std::unique_ptr<Sprite>(Sprite::Create(33, { 84,650 - 16 - 96 }));

	//�h�A���J����UI
	spriteDoorOpen = std::unique_ptr<Sprite>(Sprite::Create(45, { 990, 850 }));
	spriteDoorOpen->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));

	//�~�j�}�b�v�̘g
	spriteMapBack = std::unique_ptr<Sprite>(Sprite::Create(5, { -16 + 100,650 - 16 - 96 }));
	spriteMapFrame = std::unique_ptr<Sprite>(Sprite::Create(26, { -16 + 100,650 - 16 - 96 }));
}

void MapChip::InitializeValue()
{
	MapCreate();													//�}�b�v����
}

void MapChip::MapCreate()
{
	//�}�b�v�̐���
	MapRandam(mapWallLeftUp, mapWallLeftUp1, 0, 0);											//����
	MapRandam(mapWallLeftCenter, mapWallLeftCenter1, 0, 1);									//�����S
	MapRandam(mapWallLeftDown, mapWallLeftDown1, 0, 2);										//����
	MapRandam(mapWallCenterUp, mapWallCenterUp1, 1, 0);										//���S��
	MapRandam(mapWallCenterCenter, mapWallCenterCenter1, 1, 1);								//���S���S
	MapRandam(mapWallCenterDown, mapWallCenterDown1, 1, 2);									//���S��
	MapRandam(mapWallRightUp, mapWallRightUp1, 2, 0);										//�E��
	MapRandam(mapWallRightCenter, mapWallRightCenter1, 2, 1);								//�E���S
	MapRandam(mapWallRightDown, mapWallRightDown1, 2, 2);									//�E��
}

void MapChip::MapRandam(int mapArea[AREAVALUE][AREAVALUE], int mapArea2[AREAVALUE][AREAVALUE],int X,int Z)
{
	//�}�b�v�I��
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<>rand2(0, 1);//0~2�͈̔�
	int num = rand2(mt);

	//�}�b�v�̊��蓖��
	for (int z = 0; z < MAPVALUE / MAXAREA; z++){
		for (int x = 0; x < MAPVALUE / MAXAREA; x++){
			if (num == 0){mapWall[z + (MAPAREAVALUE * Z)][x + (MAPAREAVALUE * X)] = mapArea2[z][x];}//�}�b�v�̎�ނP
			else if (num == 1){mapWall[z + (MAPAREAVALUE * Z)][x + (MAPAREAVALUE * X)] = mapArea[z][x];}//�}�b�v�̎�ނQ
		}
	}
}

void MapChip::Update(XMFLOAT3 pos, XMFLOAT2 mapPos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3)
{	
	//�~�j�}�b�v�ړ�
	MapUIUpdate(mapPos);

	//�X�e�[�W�I�u�W�F�N�g�̃A�b�v�f�[�g
	StageUpdate(pos,enemyPos1, enemyPos2,enemyPos3);			

	//�}�b�v���ł̃v���C���[�̈ʒu�̃A�b�v�f�[�g
	PlayerPosConvertMap(pos);

	//�N���X�^���֘A
	CrystalUpdate(pos);

	//�G��~
	TimeStop();

	//�X�|�b�g
	EnemyDisplay();
}

void MapChip::MapUIUpdate(XMFLOAT2 mapPos)
{
	//�~�j�}�b�v�̕ǈړ�
	for (int x = 0; x < MAPVALUE; x++) {
		for (int y = 0; y < MAPVALUE; y++) {
			spriteMapWall[y][x]->SetPosition({ mapPos.x - MAPWALLSIZE + 100 + (MAPWALLSIZE * (MAPVALUE - x)), mapPos.y + 650 + (MAPWALLSIZE * y) });
		}
	}

	//�~�j�}�b�v�̃N���X�^���ړ�
	for (int i = 0; i < CRYSTALVALUE; i++) {
		spriteCrystal[i]->SetPosition({ mapPos.x + mapCrystalPos[i].x, mapPos.y + mapCrystalPos[i].y });
	}
}

void MapChip::StageUpdate(XMFLOAT3 pos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3)
{
	//���C�g�̒l����
	lightSilen = LightAction();

	//�h�A�̃A�b�v�f�[�g
	for (int i = 0; i < DOORVALUE; i++){
		objMapDoor[i]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}

	//�N���X�^���̃A�b�v�f�[�g
	for (int i = 0; i < CRYSTALVALUE; i++){
		objCrystal[i]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(0.0f, 0.0f, 0.0f), lightSilen, 1);
	}

	//�}�b�v�̃I�u�W�F�N�g�̃A�b�v�f�[�g
	MapUpdate(enemyPos1, enemyPos2, enemyPos3);

	//�h�A�̃I�[�v��
	DoorOpen(pos);
}

void MapChip::MapUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3)
{
	for (int x = 0; x < MAPAREAVALUE; x++){
		for (int z = 0; z < MAPAREAVALUE; z++){
			//�_�Ŋ֘A
			int lightFlag = lightSilen;
			if (ArrayValue(68.0f + (-24.0f * (6 - x)), -76.0f + (24.0f * z)) == 1) {
				lightFlag = 0;
			}
			
			//�I�u�W�F�N�g�̃A�b�v�f�[�g
			MapObjUpdate(enemyPos1, enemyPos2, enemyPos3, x, z, lightFlag);
			
			//���Ɗz���̃A�b�v�f�[�g
			DeskAndFrameUpdate(enemyPos1, enemyPos2, enemyPos3, lightFlag);
		}
	}
}

void MapChip::MapObjUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3, int x, int z, int lightFlag)
{
	for (int j = 0; j < MAXAREA; j++) {
		for (int k = 0; k < MAXAREA; k++) {
			//�ǂ̃A�b�v�f�[�g
			objMapWall[j + MAXAREA * z][k + MAXAREA * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);

			//�V��̃A�b�v�f�[�g	
			objCeiling[j + MAXAREA * z][k + MAXAREA * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);

			//���̃A�b�v�f�[�g
			objFloor[j + MAXAREA * z][k + MAXAREA * x]->Update(enemyPos1, enemyPos2, enemyPos3, XMFLOAT3(68.0f + (-24.0f * (6 - x)), 4.0f, -76.0f + (24.0f * z)), lightFlag, 0);
		}
	}
}

void MapChip::DeskAndFrameUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3,int lightFlag)
{
	//�G��Ɗ��̃A�b�v�f�[�g
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

void MapChip::DoorOpen(XMFLOAT3 pos)
{
	//�v���C���[�̃}�b�v�̍��W
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((MAPVALUE + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((MAPVALUE + 1) / 2));

	//�h�A�֘A
	if (gateOpenFlag == true && doorAngle[0] > 0){
		for (int i = 0; i < DOORVALUE; i++) {
			doorAngle[i] += moveDoorAngle[i];
		}
		mapWall[12][10] = 0;
		mapWall[8][10] = 0;
	}

	//�h�A�̊p�x���Z�b�g
	for (int i = 0; i < DOORVALUE; i++){
		objMapDoor[i]->SetRotation(XMFLOAT3({ 0.0f,doorAngle[i],0.0f }));
	}	

	//�Q�[�g�I�[�v��
	if (Input::GetInstance()->KeybordTrigger(DIK_E) && mapX == 10 && mapY == 9){
		gateOpenFlag = true;
	}
}

void MapChip::PlayerPosConvertMap(XMFLOAT3 pos)
{
	//�v���C���[�̍��W���}�b�v�`�b�v�ɕϊ�
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
	//�N���X�^���֘A
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
	
	//�N���X�^�����肵����
	if (number == 0){
		allGetFlag = true;
	}

	//�����̃t�H���g
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
	//�w�肵���ʒu�̃}�b�v�̏��擾
	int mapY = int((y / WALLSIZE) + ((MAPVALUE+1) / 2));
	int mapX = int((x / WALLSIZE) + ((MAPVALUE+1) / 2));
	return mapWall[mapY][mapX];
}

void MapChip::Draw()
{
	//�N���X�^��
	for (int i = 0; i < CRYSTALVALUE; i++){
		if(crystalGetFlag[i] == false){
			objCrystal[i]->Draw();
		}
	}

	//�h�A
	for (int i = 0; i < DOORVALUE; i++){
		objMapDoor[i]->Draw();
	}

	//�G��
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

void MapChip::DrawSprite(XMFLOAT3 pos)
{
	//�}�b�v���̍��W�n�̎擾
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((MAPVALUE + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((MAPVALUE + 1) / 2));
	
	//�~�j�}�b�v�̗�
	spriteMapBack->Draw(1.0f);//�X�|�b�g���ĂȂ���
	if (displayFlag) {
		spriteSpotEffect->Draw(1.0f);//�X�|�b�g��
	}

	//��
	for (int x = 0; x < MAPVALUE; x++){
		for (int y = 0; y < MAPVALUE; y++){
			if (mapWall[y][x] == 1 && spriteMapWall[y][x]->GetPosition().x < 420 && spriteMapWall[y][x]->GetPosition().x > 100
				&& spriteMapWall[y][x]->GetPosition().y > 650 && spriteMapWall[y][x]->GetPosition().y < 986){
				spriteMapWall[y][x]->Draw(1.0f);
			}
		}
	}

	//�N���X�^��
	for (int i = 0; i < CRYSTALVALUE; i++){
		if (crystalGetFlag[i] == false && spriteCrystal[i]->GetPosition().x < 420 && spriteCrystal[i]->GetPosition().x > 100
			&& spriteCrystal[i]->GetPosition().y > 650 && spriteCrystal[i]->GetPosition().y < 986){
			spriteCrystal[i]->Draw(1.0f);
		}
	}

	//�~�j�}�b�v�̃t���[��
	if (!displayFlag) {
		spriteMapFrame->Draw(1.0f);
	}
	
	//����
	for (int i = 0; i < MAXNUMUBER; i++){
		if (number == i + 1){
			spriteNumberNum1[number - 1]->Draw(1.0f);
		}
		if (number == MAXNUMUBERTENNUM) {
			spriteNumberNum10[i]->Draw(1.0f);
		}
	}
	
	//�X�|�b�g�t�H���g
	if (AlphaFlag(spotSprieteTime ,displayFlag)){
		spotSprieteTime++;
		spriteEnemySpot->Draw(spotAlpha);
	}
	
	//�X�g�b�v�t�H���g
	if (AlphaFlag(stopSprieteTime ,stopFlag)){
		stopSprieteTime++;
		spriteEnemyStop->Draw(stopAlpha);
	}
	
	//�Q�[�g�J���t���O
	if (GateOpen(mapY,mapX)){
		spriteDoorOpen->Draw(1.0f);
	}
}

bool MapChip::AlphaFlag(float time, bool flag)
{
	if (time < MAXALPHATIME && flag) {
		return true;
	}
	return false;
}

bool MapChip::GateOpen(int mapX, int mapY)
{
	if (gateOpenFlag == false && mapX == 10 && mapY == 9)
	{
		return true;
	}
	return false;
}

void MapChip::TimeStop()
{
	//�G��~
	if (crystalGetFlag[5] && stopTime == 0){
		stopFlag = true;
	}
	if (stopFlag){
		stopTime++;
	}
	if (stopTime > MAXSTOPTAIME){
		stopFlag = false;
	}
	
	//�X�g�b�v�t�H���g�֘A
	if (FontAlphaCalculation(stopSprieteTime,stopFlag)){
		stopAlpha -= ALPHAMINUSVALUE;
	}
	if (FontSizeCalculation(stopSprieteTime, stopFontSize, stopFlag)) {
		stopFontSize.x -= MAXFONTMINUSX;
		stopFontSize.y -= MAXFONTMINUSY;
		spriteEnemyStop->SetSize(stopFontSize);
	}
}

void MapChip::EnemyDisplay()
{
	//�G�X�|�b�g
	if (crystalGetFlag[3] && displayTime == 0){
		displayFlag = true;
	}
	if (displayFlag){
		displayTime++;
	}
	if (displayTime > MAXSPOTTIME){
		displayFlag = false;
	}

	//�X�|�b�g�t�H���g�֘A
	if (FontAlphaCalculation(spotSprieteTime ,displayFlag)){
		spotAlpha -= ALPHAMINUSVALUE;
	}
	if (FontSizeCalculation(spotSprieteTime,spotFontSize,displayFlag)){
		spotFontSize.x -= MAXFONTMINUSX;
		spotFontSize.y -= MAXFONTMINUSY;
		spriteEnemySpot->SetSize(spotFontSize);
	}
}

bool MapChip::FontAlphaCalculation(float time, bool flag)
{
	if (time > 60 && time < 80 && flag) {
		return true;
	}
	return false;
}

bool MapChip::FontSizeCalculation(float time, XMFLOAT2 size, bool flag)
{
	if (time < 60 && size.x > 1200 && flag){
		return true;
	}
	return false;
}

bool MapChip::LightAction()
{
	//���C�g�̓_�ł����Ȃ�
	if (!lightAction){
		return true;
	}

	//��莞�Ԍo�ߌド�C�g�̃J�E���g��0�ɂ���
	lightCount++;
	if (lightCount > lightDelayTime * 15){
		lightCount = 0;
	}

	//���C�g�̓_��
	for (int i = 1; i < MAXACTIONCOUNT; i++){
		if (lightCount > lightDelayTime * i){
			if (i % 2 == 0){
				return true;
			}
			else if (i % 2 == 1){
				return false;
			}
		}
	}
	return true;
}
