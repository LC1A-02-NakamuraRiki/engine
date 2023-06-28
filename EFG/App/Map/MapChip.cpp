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
	//�}�b�v������
	InitMapObject();
	
	//�X�v���C�g������
	mapUI = std::make_unique<MapUI>();
	mapUI->InitSprite();
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
		if(i == SPOTCRYSTALNUM){ objCrystal[SPOTCRYSTALNUM] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal.get())); }
		if (i == STOPCRYSTALNUM) { objCrystal[STOPCRYSTALNUM] = std::unique_ptr<Object3d>(Object3d::Create(modelItemCrystal2.get())); }
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

void MapChip::InitializeValue()
{
	MapCreate();													//�}�b�v����
}

void MapChip::MapCreate()
{
	//�}�b�v�̐���
	MapRandam(mapWallLeftUp, mapWallLeftUp1, UpOrLeft, UpOrLeft);											//����
	MapRandam(mapWallLeftCenter, mapWallLeftCenter1, UpOrLeft, Center);										//�����S
	MapRandam(mapWallLeftDown, mapWallLeftDown1, UpOrLeft, DownOrRight);									//����
	MapRandam(mapWallCenterUp, mapWallCenterUp1, Center, UpOrLeft);											//���S��
	MapRandam(mapWallCenterCenter, mapWallCenterCenter1, Center, Center);									//���S���S
	MapRandam(mapWallCenterDown, mapWallCenterDown1, Center, DownOrRight);									//���S��
	MapRandam(mapWallRightUp, mapWallRightUp1, 2, UpOrLeft);												//�E��
	MapRandam(mapWallRightCenter, mapWallRightCenter1, DownOrRight, Center);								//�E���S
	MapRandam(mapWallRightDown, mapWallRightDown1, DownOrRight, DownOrRight);								//�E��
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
	mapUI->MapUIUpdate(mapPos,number);

	//�X�e�[�W�I�u�W�F�N�g�̃A�b�v�f�[�g
	StageUpdate(pos,enemyPos1, enemyPos2,enemyPos3);			

	//�}�b�v���ł̃v���C���[�̈ʒu�̃A�b�v�f�[�g
	PlayerPosConvertMap(pos);

	//�N���X�^���֘A
	CrystalUpdate(pos);

	//�G��~
	mapUI->TimeStop();

	//�X�|�b�g
	mapUI->EnemyDisplay();
}

void MapChip::StageUpdate(XMFLOAT3 pos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3)
{
	//���C�g�̒l����
	lightSilen = MapEffect::LightAction(lightAction, lightCount);

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

void MapChip::MiniMapDraw()
{
	mapUI->DrawSprite(pos, mapWall, crystalGetFlag, number, stopFlag, spotAlphaFlag, stopAlphaFlag, gateOpen);
}