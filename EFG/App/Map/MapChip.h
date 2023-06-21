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
	const int MAPAREAVALUE = 7;															//1�G���A�̃T�C�Y
	const int MAXAREA = 3;																//�G���A�̐�
	const int CRYSTALVALUE = 15;														//�N���X�^���̐�
	const int DOORVALUE = 4;															//�h�A�̐�
	const int MAXNUMBER = 10;															//�i���o�[�ő�
	const int MAXSTOPTAIME = 300;														//�}�b�N�X�X�g�b�v�^�C��
	const int MAXSPOTTIME = 600;														//�}�b�N�X�X�|�b�g�^�C��
	const int MAXNUMUBER = 9;															//�i���o�[�ő�
	const int MAXNUMUBERTENNUM = 10;													//�i���o�[�ő�
	const int MAXNUMUBERNUM = 11;														//�i���o�[�ő�
	const int MAXACTIONCOUNT = 5;														//�A�N�V�����̍ő�
	const int MAXALPHATIME = 80;														//�A���t�@���Ԃ̍ő�
	const float MAXFONTMINUSX = 1200;													//�t�H���g���������Ȃ�ۂ̒lX
	const float MAXFONTMINUSY = 200;													//�t�H���g���������Ȃ�ۂ̒lY
	const float ALPHAMINUSVALUE = 0.05f;												//�A���t�@�̃}�C�i�X�l
public:
	//
	~MapChip();
	
	//�ŏ��̏�����
	void Initialize();

	//�}�b�v������
	void InitMapObject();

	//���f���̓ǂݍ���
	void LoadModel();

	//�}�b�v�̓ǂݍ���
	void LoadMap();

	//�N���X�^��������
	void InitCrystal();

	//�h�A������
	void InitDoor();

	//�X�v���C�g������
	void InitSprite();

	//�^�C�g�����̏�����
	void InitializeValue();

	//�}�b�v�쐻
	void MapCreate();

	//�}�b�v�̃����_���r�o
	void MapRandam(int mapArea[AREAVALUE][AREAVALUE],int mapArea2[AREAVALUE][AREAVALUE], int X, int Z);
	
	//�S�̃A�b�v�f�[�g
	void Update(XMFLOAT3 pos, XMFLOAT2 mapPos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);

	//�~�j�}�b�v�ړ�
	void MapUIUpdate(XMFLOAT2 mapPos);

	//�X�e�[�W�A�b�v�f�[�g
	void StageUpdate(XMFLOAT3 pos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);
	
	//�}�b�v�A�b�v�f�[�g
	void MapUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);
	
	//OBJ�A�b�v�f�[�g
	void MapObjUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3, int x, int z, int lightFlag);

	//�N���X�^���A�b�v�f�[�g
	void CrystalUpdate(XMFLOAT3 pos);
	
	//���ƊG��A�b�v�f�[�g
	void DeskAndFrameUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3, int lightFlag);
	
	//�h�A�J��
	void DoorOpen(XMFLOAT3 pos);
	
	//�v���C���[�̈ʒu���}�b�v�`�b�v�ɕϊ�
	void PlayerPosConvertMap(XMFLOAT3 pos);

	//���W����}�b�v�`�b�v�z��̎Z�o
	int ArrayValue(float x, float y);
	
	//�`��
	void Draw();

	//�X�v���C�g�`��
	void DrawSprite(XMFLOAT3 pos);

	//�A���t�@�̎���
	bool AlphaFlag(float time, bool flag);

	//�Q�[�g�I�[�v��
	bool GateOpen(int mapX,int mapY);

	//���Ԓ�~
	void TimeStop();

	//�G�X�|�b�g
	void EnemyDisplay();

	//�t�H���g��\������v�Z
	bool FontAlphaCalculation(float time,bool flag);

	//�t�H���g��\������v�Z
	bool FontSizeCalculation(float time, XMFLOAT2 size,bool flag);

	//�}�b�v�`�b�v�̏��擾
	int GetArrayValue(int x, int z) { return mapWall[z][x]; }			

	//�}�b�v�`�b�v�ŕ\�����v���C���[�̈ʒu�擾
	int GetPlayerArrayValue(int x, int z) { return mapPlayer[x][z]; }	

	//�N���X�^�������ׂĎ�������t���O�擾
	bool GetAllGetFlag() { return allGetFlag; }							

	//�X�g�b�v�t���O�擾
	bool GetStopFlag() { return stopFlag; }								

	//�X�|�b�g�t���O�擾
	bool GetDisplayFlag() { return displayFlag; }					

	//�N���X�^�����Ă��邩�t���O�擾
	bool GetCrystalGetFlag(int no) { return crystalGetFlag[no]; }		

	//�Q�[�g���J�������t���O�擾
	bool GetGateOpenFlag() { return gateOpenFlag; }						

	//���C�g�_��
	bool LightAction();																	

	//�t���O�Z�b�g
	bool SetLightAction(bool actionFlag) { return this->lightAction = actionFlag; }		
private:
	std::unique_ptr<Model> modelMapWall;												//�ǃ��f��
	std::unique_ptr<Model> modelCeiling;												//���C�g���f��
	std::unique_ptr<Model> modelFlat;													//�V�䃂�f��
	std::unique_ptr<Model> modelCrystal;												//�N���X�^�����f��
	std::unique_ptr<Model> modelItemCrystal;											//�A�C�e���N���X�^�����f��
	std::unique_ptr<Model> modelItemCrystal2;											//�A�C�e���N���X�^�����f��
	std::unique_ptr<Model> modelFloor;													//�����f��
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objMapWall;			//�ǃI�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objCeiling;			//���C�g�I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objFloor;				//���̃I�u�W�F�N�g
	std::array <std::unique_ptr<Object3d>, 15> objCrystal;								//�N���X�^���I�u�W�F�N�g
	std::unique_ptr<Sprite> spriteDoorOpen;												//�h�AUI
	std::array < std::unique_ptr<Model>, 4> modelDoor;									//�h�A���f��
	std::array<float, 4> doorAngle = { 90, 270,90,270 };								//�h�A�p�x
	std::array < std::unique_ptr<Object3d>, 4> objMapDoor;								//�h�A�I�u�W�F�N�g
	bool gateOpenFlag = false;															//�Q�[�g�󂢂���
	std::array<std::array<int, 21>, 21> mapWall = {};									//�}�b�v���	
	std::array<std::array<int, 21>, 21> mapPlayer = {};									//�v���C���[�̈ʒu���W��	
	bool allGetFlag = false;															//�N���X�^���S���Ƃꂽ��
	int stopTime = 0;																	//�X�g�b�v�^�C��
	bool stopFlag = false;																//�X�g�b�v�t���O
	int displayTime = 0;																//�X�|�b�g�^�C��
	bool displayFlag = false;															//�X�|�b�g�t���O
	std::array < std::array < std::unique_ptr<Sprite>,21>,21> spriteMapWall;			//�~�j�}�b�v��
	std::unique_ptr<Sprite> spriteMapBack;												//�~�j�}�b�v�̔w�i
	std::unique_ptr<Sprite> spriteMapFrame;												//�~�j�}�b�v�̃t���[��				
	std::array <std::unique_ptr<Sprite>,15> spriteCrystal;								//�~�j�}�b�v�̃N���X�^��
	std::array <std::unique_ptr<Sprite>,10> spriteNumberNum1;							//�i���o�[1�̂��炢
	std::array <std::unique_ptr<Sprite>,10> spriteNumberNum10;							//�i���o�[10�̂��炢
	std::unique_ptr<Sprite> spriteEnemyStop;											//�G��~
	XMFLOAT2 stopFontSize = { 1200.0f * 10, 200.0f * 10 };								//�t�H���g�T�C�Y
	int stopSprieteTime = 0;															//����
	float stopAlpha = 1.0f;																//�A���t�@�l
	std::unique_ptr<Sprite> spriteEnemySpot;											//�G�X�|�b�g
	XMFLOAT2 spotFontSize = { 1200.0f * 10, 200.0f * 10 };								//�t�H���g�T�C�Y
	int spotSprieteTime = 0;															//����
	float spotAlpha = 1.0f;																//�A���t�@�l
	std::unique_ptr<Sprite> spriteSpotEffect;											//�X�|�b�g�G�t�F�N�g
	int number = 11;																	//����
	std::unique_ptr<Model> modelPictureFrame;											//�G��̃��f��
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame1;		//�G��I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame2;		//�G��I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame3;		//�G��I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame4;		//�G��I�u�W�F�N�g
	std::unique_ptr<Model> modelDesk;													//�����f��
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk1;				//���I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk2;				//���I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk3;				//���I�u�W�F�N�g
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk4;				//���I�u�W�F�N�g
	bool lightAction = 0;																//���C�g�_�Ńt���O
	int lightCount = 0;																	//���C�g�_�ł̃J�E���g
	EditData* editData = nullptr;														//�}�b�v�̃f�[�^
	std::map<std::string, Model*> models;												//���f���f�[�^
	std::vector<Object3d*> objects;														//�I�u�W�F�N�g�f�[�^
	EditData* randamEditData = nullptr;													//�����_���̃}�b�v�̃f�[�^
	std::map<std::string, Model*> randamModels;											//�����_���̃��f���f�[�^
	std::vector<Object3d*> randamObjects;												//�����_���̃I�u�W�F�N�g�f�[�^
	bool lightSilen = true;																//���C�g�_�Ńt���O
	int lightDelayTime = 20;

	//�����_���̂��߂̃}�b�v1
	int mapWallLeftUp[7][7] = {};
	int mapWallLeftCenter[7][7] = {};
	int mapWallLeftDown[7][7] = {};
	int mapWallCenterUp[7][7] = {};
	int mapWallCenterCenter[7][7] = {};
	int mapWallCenterDown[7][7] = {};
	int mapWallRightUp[7][7] = {};
	int mapWallRightCenter[7][7] = {};
	int mapWallRightDown[7][7] = {};

	//�����_���̂��߂̃}�b�v2
	int mapWallLeftUp1[7][7] = {};
	int mapWallLeftCenter1[7][7] = {};
	int mapWallLeftDown1[7][7] = {};
	int mapWallCenterUp1[7][7] = {};
	int mapWallCenterCenter1[7][7] = {};
	int mapWallCenterDown1[7][7] = {};
	int mapWallRightUp1[7][7] = {};
	int mapWallRightCenter1[7][7] = {};
	int mapWallRightDown1[7][7] = {};

	//�N���X�^���̈ʒu3D
	std::array<XMFLOAT3, 15> crystalPos = { XMFLOAT3({ 1 * WALLSIZE - (21 * WALLSIZE / 2),  1.0f, 1 * WALLSIZE - (21 * WALLSIZE / 2)   }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),  1.0f, 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 16 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),  1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }), };

	//�N���X�^���̈ʒu2D
	std::array<XMFLOAT2, 15> mapCrystalPos = { XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 1)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 1)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 1)}, XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 10)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 16)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 10)},XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 19)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 19)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 19)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 7)} ,XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 13)},
	XMFLOAT2{100 + (MAPWALLSIZE * 13),650 + (MAPWALLSIZE * 13)},XMFLOAT2{100 + (MAPWALLSIZE * 7),650 + (MAPWALLSIZE * 13)}, XMFLOAT2{100 + (MAPWALLSIZE * 13),650 + (MAPWALLSIZE * 7)}, XMFLOAT2{100 + (MAPWALLSIZE * 7),650 + (MAPWALLSIZE * 7)}, };

	//�h�A�I�u�W�F�N�g�|�W�V����
	std::array <XMFLOAT3,4> mapDoorPos = { XMFLOAT3({ -0.2f,0.2f,-16.0f }),
	XMFLOAT3({ -7.8f,0.2f,-16.0f }),
	XMFLOAT3({ -0.2f,0.2f,8.0f   }),
	XMFLOAT3({ -7.8f,0.2f,8.0f   }) };			

	//�h�A�̊p�x�ύX�l
	std::array <float, 4> moveDoorAngle = {-10,10,10,-10};

	//�N���X�^���������
	std::array<bool, 15> crystalGetFlag = { false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };
};