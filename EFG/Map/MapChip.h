#pragma once
#include <DirectXMath.h>
#include "Object3d.h"
#include "Sprite.h"
#include"LoadCSV.h"
#include <memory>
#include <array>
#include <map>
#include "EditLoader.h"

#define AREAVALUE (7) //���̍ő喇��

class MapChip
{
private: // �G�C���A�X
// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

	const float WALLSIZE = 8.0f;														//�ǂ̑傫��
	const float MAPWALLSIZE = 16.0f;													//�~�j�}�b�v�̕ǂ̑傫��
	const int MAPVALUE = 21;															//�}�b�v�̍ő�T�C�Y
	const int MAPAREAVALUE = 7;
	const int CRYSTALVALUE = 11;
	const int DOORVALUE = 4;
	const int MAXNUMBER = 10;
public:
	~MapChip();
	void Initialize();//�ŏ��̏�����
	void InitializeValue();//�^�C�g�����̏�����
	void MapCreate();//�}�b�v�쐻
	void MapRandam(int mapArea[AREAVALUE][AREAVALUE],int mapArea2[AREAVALUE][AREAVALUE], int X, int Z);
	void MapMove(XMFLOAT2 mapPos);//�~�j�}�b�v�ړ�
	void Update(XMFLOAT3 pos, XMFLOAT2 mapPos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);//�A�b�v�f�[�g
	void StageUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);
	void DoorOpen(XMFLOAT3 pos);
	void PlayerPosConvertMap(XMFLOAT3 pos);
	void CrystalUpdate(XMFLOAT3 pos);
	int ArrayValue(float x, float y);//���W����}�b�v�`�b�v�z��̎Z�o
	void Draw();//�`��
	void DrawSprite(XMFLOAT3 pos);//�X�v���C�g�`��
	void TimeStop();//���Ԓ�~
	void EnemyDisplay();//�G�X�|�b�g

	int GetArrayValue(int x, int z) { return mapWall[z][x]; }			//�}�b�v�`�b�v�̏��擾
	int GetPlayerArrayValue(int x, int z) { return mapPlayer[x][z]; }	//�}�b�v�`�b�v�ŕ\�����v���C���[�̈ʒu�擾
	bool GetAllGetFlag() { return allGetFlag; }							//�N���X�^�������ׂĎ�������t���O�擾
	bool GetStopFlag() { return stopFlag; }								//�X�g�b�v�t���O�擾
	bool GetDisplayFlag() { return displayFlag; }						//�X�|�b�g�t���O�擾
	bool GetCrystalGetFlag(int no) { return crystalGetFlag[no]; }		//�N���X�^�����Ă��邩�t���O�擾
	bool GetGateOpenFlag() { return gateOpenFlag; }						//�Q�[�g���J�������t���O�擾

	bool LightAction();																	//���C�g�_��
	bool SetLightAction(bool actionFlag) { return this->lightAction = actionFlag; }		//�t���O�Z�b�g
private:
	std::unique_ptr<Model> modelMapWall;												//�ǃ��f��
	std::unique_ptr<Model> modelCeiling;												//���C�g���f��
	std::unique_ptr<Model> modelFlat;													//�V�䃂�f��
	std::unique_ptr<Model> modelFloor;													//�����f��
	std::unique_ptr<Model> modelCrystal;												//�N���X�^�����f��
	std::unique_ptr<Model> modelItemCrystal;											//�A�C�e���N���X�^�����f��
	std::unique_ptr<Model> modelItemCrystal2;											//�A�C�e���N���X�^�����f��
	std::array <std::unique_ptr<Object3d>, 11> objCrystal;//�N���X�^���I�u�W�F�N�g

	std::unique_ptr<Sprite> spriteDoorOpen;//�h�AUI
	std::array < std::unique_ptr<Model>, 4> modelDoor;//�h�A���f��
	std::array<float, 4> doorAngle = { 90, 270,90,270 };//�h�A�p�x
	std::array < std::unique_ptr<Object3d>, 4> objMapDoor;//�h�A�I�u�W�F�N�g
	bool gateOpenFlag = false;//�Q�[�g�󂢂���

	//�N���X�^���̈ʒu3D
	std::array<XMFLOAT3, 11> crystalPos = { XMFLOAT3({ 1 * WALLSIZE - (21 * WALLSIZE / 2),  1.0f, 1 * WALLSIZE - (21 * WALLSIZE / 2)   }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),  1.0f, 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 16 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),  1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }) };
	
	//�N���X�^���̈ʒu2D
	std::array<XMFLOAT2, 11> mapCrystalPos = { XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 1)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 1)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 1)}, XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 10)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 16)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 10)},XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 19)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 19)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 19)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 7)} ,XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 13)}, };

	std::array<bool, 11> crystalGetFlag = { false,false,false,false,false,false,false,false,false,false,false };//�N���X�^���������
	
	
	//�}�b�v���
	std::array<std::array<int, 21>, 21> mapWall = {};
	//�v���C���[�̈ʒu���W��
	std::array<std::array<int, 21>, 21> mapPlayer = {};

	bool allGetFlag = false;//�N���X�^���S���Ƃꂽ��

	int stopTime = 0;//�X�g�b�v�^�C��
	bool stopFlag = false;//�X�g�b�v�t���O

	int displayTime = 0;//�X�|�b�g�^�C��
	bool displayFlag = false;//�X�|�b�g�t���O

	std::array < std::array < std::unique_ptr<Sprite>,21>,21> spriteMapWall;//�~�j�}�b�v��
	std::unique_ptr<Sprite> spriteMapBack;//�~�j�}�b�v�̔w�i
	std::unique_ptr<Sprite> spriteMapFrame;//�~�j�}�b�v�̃t���[��
					
	std::array <std::unique_ptr<Sprite>,11> spriteCrystal;//�~�j�}�b�v�̃N���X�^��
	std::array <std::unique_ptr<Sprite>,10> spriteNumberNum1;//�i���o�[1�̂��炢
	std::array <std::unique_ptr<Sprite>,10> spriteNumberNum10;//�i���o�[10�̂��炢

	std::unique_ptr<Sprite> spriteEnemyStop;//�G��~
	XMFLOAT2 stopFontSize = { 1200.0f * 10, 200.0f * 10 };//�t�H���g�T�C�Y
	int stopSprieteTime = 0;//����
	float stopAlpha = 1.0f;//�A���t�@�l

	std::unique_ptr<Sprite> spriteEnemySpot;//�G�X�|�b�g
	XMFLOAT2 spotFontSize = { 1200.0f * 10, 200.0f * 10 };//�t�H���g�T�C�Y
	int spotSprieteTime = 0;//����
	float spotAlpha = 1.0f;//�A���t�@�l
	
	std::unique_ptr<Sprite> spriteSpotEffect;//�X�|�b�g�G�t�F�N�g
	int number = 11;//����

	std::unique_ptr<Model> modelPictureFrame;//�G��̃��f��
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame1;//�G��I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame2;//�G��I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame3;//�G��I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame4;//�G��I�u�W�F�N�g

	std::unique_ptr<Model> modelDesk;//�����f��
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk1;//���I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk2;//���I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk3;//���I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk4;//���I�u�W�F�N�g

	bool lightAction = 0;//���C�g�_�Ńt���O
	int lightCount = 0;//���C�g�_�ł̃J�E���g

	EditData* editData = nullptr;

	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;

	EditData* randamEditData = nullptr;
	std::map<std::string, Model*> randamModels;
	std::vector<Object3d*> randamObjects;

	//�����_���̂��߂̃}�b�v1
	int mapWallLeftUp[7][7] = {
		1,1,1,1,1,1,1,
		1,2,0,0,0,3,0,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,5,0,
		1,5,0,0,3,10,1,
		1,0,1,1,0,1,1
	};
	int mapWallLeftCenter[7][7] = {
		1,8,4,1,0,1,1,
		1,1,5,0,7,1,1,
		1,2,10,1,5,0,0,
		1,0,1,1,0,1,1,
		1,8,4,1,5,0,0,
		1,1,5,0,7,1,1,
		1,2,10,1,0,1,1
	};
	int mapWallLeftDown[7][7] = {
		1,0,1,1,0,1,1,
		1,5,0,0,9,4,1,
		1,0,1,1,1,5,0,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,8,0,0,0,9,0,
		1,1,1,1,1,1,1
	};
	int mapWallCenterUp[7][7] = {
		1,1,1,1,1,1,1,
		4,1,2,0,4,1,2,
		8,3,10,1,8,3,10,
		1,0,1,1,1,0,1,
		0,9,3,0,3,9,0,
		1,1,0,1,0,1,1,
		1,1,0,1,0,1,1 };
	int mapWallCenterCenter[7][7] = {
		2,0,9,3,9,0,4,
		0,1,1,11,1,1,0,
		7,1,1,0,1,1,5,
		0,1,1,0,1,1,0,
		7,1,1,0,1,1,5,
		0,1,1,11,1,1,0,
		8,0,3,9,3,0,10
	};
	int mapWallCenterDown[7][7] = {
		1,1,0,1,0,1,1,
		1,1,0,1,0,1,1,
		0,3,9,0,9,3,0,
		1,0,1,1,1,0,1,
		2,9,4,1,2,9,4,
		10,1,8,0,10,1,8,
		1,1,1,1,1,1,1
	};
	int mapWallRightUp[7][7] = {
		1,1,1,1,1,1,1,
		0,3,0,0,0,4,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		0,7,1,1,1,0,1,
		1,8,3,0,0,7,1,
		1,1,0,1,1,0,1
	};
	int mapWallRightCenter[7][7] = {
		1,1,0,1,2,10,1,
		1,1,5,0,7,1,1,
		0,0,7,1,8,4,1,
		1,1,0,1,1,0,1,
		0,0,7,1,2,10,1,
		1,1,5,0,7,1,1,
		1,1,0,1,8,4,1
	};
	int mapWallRightDown[7][7] = {
		1,1,0,1,1,0,1,
		1,2,9,0,0,7,1,
		0,7,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		0,9,0,0,0,10,1,
		1,1,1,1,1,1,1
	};

	//�����_���̂��߂̃}�b�v2
	int mapWallLeftUp1[7][7] = {
		1,1,1,1,1,1,1,
		1,2,0,0,0,3,0,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,5,0,
		1,5,0,0,3,10,1,
		1,0,1,1,0,1,1
	};
	int mapWallLeftCenter1[7][7] = {
		1,8,4,1,0,1,1,
		1,1,5,0,7,1,1,
		1,2,10,1,5,0,0,
		1,0,1,1,0,1,1,
		1,8,4,1,5,0,0,
		1,1,5,0,7,1,1,
		1,2,10,1,0,1,1
	};
	int mapWallLeftDown1[7][7] = {
		1,0,1,1,0,1,1,
		1,5,0,0,9,4,1,
		1,0,1,1,1,5,0,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,8,0,0,0,9,0,
		1,1,1,1,1,1,1
	};
	int mapWallCenterUp1[7][7] = {
		1,1,1,1,1,1,1,
		4,1,2,0,4,1,2,
		8,3,10,1,8,3,10,
		1,0,1,1,1,0,1,
		0,9,3,0,3,9,0,
		1,1,0,1,0,1,1,
		1,1,0,1,0,1,1 };
	int mapWallCenterCenter1[7][7] = {
		2,0,9,3,9,0,4,
		0,1,1,11,1,1,0,
		7,1,1,0,1,1,5,
		0,1,1,0,1,1,0,
		7,1,1,0,1,1,5,
		0,1,1,11,1,1,0,
		8,0,3,9,3,0,10
	};
	int mapWallCenterDown1[7][7] = {
		1,1,0,1,0,1,1,
		1,1,0,1,0,1,1,
		0,3,9,0,9,3,0,
		1,0,1,1,1,0,1,
		2,9,4,1,2,9,4,
		10,1,8,0,10,1,8,
		1,1,1,1,1,1,1
	};
	int mapWallRightUp1[7][7] = {
		1,1,1,1,1,1,1,
		0,3,0,0,0,4,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		0,7,1,1,1,0,1,
		1,8,3,0,0,7,1,
		1,1,0,1,1,0,1
	};
	int mapWallRightCenter1[7][7] = {
		1,1,0,1,2,10,1,
		1,1,5,0,7,1,1,
		0,0,7,1,8,4,1,
		1,1,0,1,1,0,1,
		0,0,7,1,2,10,1,
		1,1,5,0,7,1,1,
		1,1,0,1,8,4,1
	};
	int mapWallRightDown1[7][7] = {
		1,1,0,1,1,0,1,
		1,2,9,0,0,7,1,
		0,7,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		0,9,0,0,0,10,1,
		1,1,1,1,1,1,1
	};
};