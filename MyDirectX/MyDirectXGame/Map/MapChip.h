#pragma once
#include <DirectXMath.h>
#include "Object3d.h"
#include "Sprite.h"
#include"LoadCSV.h"
#include "SafeDelete.h"
#include <memory>
#include <array>
class MapChip
{
protected: // �G�C���A�X
// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	~MapChip();
	void Initialize();//�ŏ��̏�����
	void InitializeValue();//�^�C�g�����̏�����
	void MapCreate();//�}�b�v�쐻
	void MapMove(XMFLOAT2 mapPos);//�~�j�}�b�v�ړ�
	void Update(XMFLOAT3 pos, XMFLOAT2 mapPos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);//�A�b�v�f�[�g
	int ArrayValue(float x, float y);//���W����}�b�v�`�b�v�z��̎Z�o
	void Draw();//�`��
	void DrawSprite(XMFLOAT3 pos);//�X�v���C�g�`��
	void TimeStop();//���Ԓ�~
	void EnemyDisplay();//�G�X�|�b�g

	int GetArrayValue(int x, int z) { return mapWall[z][x]; }//�}�b�v�`�b�v�̏��擾
	int GetPlayerArrayValue(int x, int z) { return mapPlayer[x][z]; }//�}�b�v�`�b�v�ŕ\�����v���C���[�̈ʒu�擾
	bool GetAllGetFlag() { return allGetFlag; }//�N���X�^�������ׂĎ�������t���O�擾
	bool GetStopFlag() { return stopFlag; }//�X�g�b�v�t���O�擾
	bool GetDisplayFlag() { return displayFlag; }//�X�|�b�g�t���O�擾
	bool GetCrystalGetFlag(int no) { return crystalGetFlag[no]; }//�N���X�^�����Ă��邩�t���O�擾
	bool GetGateOpenFlag() { return gateOpenFlag; }//�Q�[�g���J�������t���O�擾

	bool LightAction();//���C�g�_��
	bool SetLightAction(bool actionFlag) {return this->lightAction = actionFlag;}//�t���O�Z�b�g
private:
	
	std::unique_ptr<Model> modelMapWall;//�ǃ��f��
	std::array < std::array < std::unique_ptr<Object3d>,21>,21> objMapWall;//�ǃI�u�W�F�N�g
	std::unique_ptr<Model> modelCeiling;//���C�g���f��
	std::unique_ptr<Model> modelFlat;//�V�䃂�f��
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objCeiling;//���C�g�I�u�W�F�N�g
	std::unique_ptr<Model> modelFloor;//�����f��
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objFloor;//���I�u�W�F�N�g
	std::unique_ptr<Model> modelCrystal;//�N���X�^�����f��
	std::unique_ptr<Model> modelItemCrystal;//�A�C�e���N���X�^�����f��
	std::array <std::unique_ptr<Object3d>, 11> objCrystal;//�N���X�^���I�u�W�F�N�g

	std::unique_ptr<Sprite> spriteDoorOpen;//�h�AUI
	std::array < std::unique_ptr<Model>,4> modelDoor;//�h�A���f��
	std::array<float, 4> doorAngle = {90, 270,90,270};//�h�A�p�x
	std::array < std::unique_ptr<Object3d>,4> objMapDoor;//�h�A�I�u�W�F�N�g
	bool gateOpenFlag = false;//�Q�[�g�󂢂���
	float wallSize = 8;//�ǂ̑傫��

	//�N���X�^���̈ʒu3D
	std::array<XMFLOAT3, 11> crystalPos = {XMFLOAT3({ 1 * wallSize - (21 * wallSize / 2),  1.0f, 1 * wallSize - (21 * wallSize / 2)   }),
	XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2), 1.0f, 1 * wallSize - (21 * wallSize / 2)   }),
	XMFLOAT3({ 19 * wallSize - (21 * wallSize / 2), 1.0f, 1 * wallSize - (21 * wallSize / 2)  }),
	XMFLOAT3({ 1 * wallSize - (21 * wallSize / 2),  1.0f, 10 * wallSize - (21 * wallSize / 2)   }),
	XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2), 1.0f, 16 * wallSize - (21 * wallSize / 2)   }),
	XMFLOAT3({ 19 * wallSize - (21 * wallSize / 2), 1.0f, 10 * wallSize - (21 * wallSize / 2)  }),
	XMFLOAT3({ 1 * wallSize - (21 * wallSize / 2),  1.0f, 19 * wallSize - (21 * wallSize / 2)  }),
	XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2), 1.0f, 19 * wallSize - (21 * wallSize / 2)  }),
	XMFLOAT3({ 19 * wallSize - (21 *  wallSize / 2),1.0f, 19 * wallSize - (21 *  wallSize / 2) }),
	XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2),1.0f, 7 * wallSize - (21 * wallSize / 2) }),
	XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2),1.0f, 13 * wallSize - (21 * wallSize / 2) })	};
	
	//�N���X�^���̈ʒu2D
	std::array<XMFLOAT2, 11> mapCrystalPos = { XMFLOAT2{100 + (16.0f * 19),650 + (16.0f * 1)},XMFLOAT2{100 + (16.0f * 10),650 + (16.0f * 1)},
	XMFLOAT2{100 + (16.0f * 1),650 + (16.0f * 1)},XMFLOAT2{100 + (16.0f * 19),650 + (16.0f * 10)},XMFLOAT2{100 + (16.0f * 10),650 + (16.0f * 16)},
	XMFLOAT2{100 + (16.0f * 1),650 + (16.0f * 10)},XMFLOAT2{100 + (16.0f * 19),650 + (16.0f * 19)},XMFLOAT2{100 + (16.0f * 10),650 + (16.0f * 19)},
	XMFLOAT2{100 + (16.0f * 1),650 + (16.0f * 19)},XMFLOAT2{100 + (16.0f * 10),650 + (16.0f * 7)},XMFLOAT2{100 + (16.0f * 10),650 + (16.0f * 13)}, };

	std::array<bool, 11> crystalGetFlag = { false,false,false,false,false,false,false,false,false,false,false };//�N���X�^���������
	int MapValue = 21;//�}�b�v�T�C�Y
	
	//�}�b�v���
	std::array<std::array<int, 21>, 21> mapWall = {};
	//�v���C���[�̈ʒu���W��
	std::array<std::array<int, 21>, 21> mapPlayer = {};

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
};